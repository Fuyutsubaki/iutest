//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_result.hpp
 * @brief		iris unit test result �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_result_HPP_D27B1599_F42F_4e2d_B3EB_FACE24C2B921_
#define INCG_IRIS_iutest_result_HPP_D27B1599_F42F_4e2d_B3EB_FACE24C2B921_

//======================================================================
// include
#include "iutest_env.hpp"
#include "internal/iutest_message.h"
#include "internal/iutest_console.hpp"

namespace iutest
{

//======================================================================
// declare
namespace detail
{
	class DefaultGlobalTestPartResultReporter;
}

//======================================================================
// class
/**
 * @brief	�e�X�g���ʂ̒ʒm�����C���^�[�t�F�C�X
*/
class TestPartResultReporterInterface
{
public:
	virtual ~TestPartResultReporterInterface(void) {}
	/**
	 * @brief	�e�X�g���ʒʒm�󂯎��֐�
	 * @param [in] result	= �e�X�g����
	*/
	virtual void ReportTestPartResult(const TestPartResult& result)	= 0;
};

/**
 * @brief	�e�X�g���ʂ������N���X
*/
class TestPartResult : public detail::iuCodeMessage
{
public:
	/**
	 * @brief	���ʂ̃^�C�v
	*/
	enum Type
	{
		kWarning = -1,		//!< �x��
		kSuccess,			//!< ����
		kNotFatalFailure,	//!< �v���I�ł͂Ȃ����s
		kFatalFailure		//!< �v���I�Ȏ��s
	};
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	file	= �t�@�C����
	 * @param [in]	line	= �s�ԍ�
	 * @param [in]	message	= ���b�Z�[�W
	 * @param [in]	type	= ���ʂ̃^�C�v
	*/
	TestPartResult(const char* file, int line, const char* message, Type type)
		: detail::iuCodeMessage(file, line, message), m_type(type) {}
	//! �R�s�[�R���X�g���N�^
	TestPartResult(const TestPartResult& rhs) : detail::iuCodeMessage(rhs)
		, m_type(rhs.m_type) {}

public:
	/**
	 * @brief	���s���ǂ���
	*/
	bool		failed(void)	const		{ return m_type != kSuccess && m_type != kWarning; }
	/**
	 * @brief	�������ǂ���
	*/
	bool		passed(void)	const		{ return !failed(); }
	/**
	 * @brief	�x�����ǂ���
	*/
	bool		warning(void)	const		{ return m_type == kWarning; }

	/**
	 * @brief	�v���I�ł͂Ȃ����s���ǂ���
	*/
	bool		nonfatally_failed(void)	const	{ return m_type == kNotFatalFailure; }

	/**
	 * @brief	�v���I�Ȏ��s���ǂ���
	*/
	bool		fatally_failed(void)	const	{ return m_type == kFatalFailure; }

	/**
	 * @brief	���R
	*/
	const char*	summary(void)	const	{ return message(); }

	/**
	 * @brief	���ʂ̃^�C�v�擾
	*/
	Type		type(void)	const		{ return m_type; }

private:
	Type	m_type;
};

//! TestPartResult print �o��
inline ::std::ostream& operator << (::std::ostream& os, const TestPartResult& result)
{
	return os << result.make_message();
}

/**
 * @brief	�e�X�g�v���p�e�B
 * @note	XML ����
*/
class TestProperty
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	key		= �L�[
	 * @param [in]	value	= �l
	*/
	TestProperty(const char* key, const char* value)
		: m_key(key), m_value(value) {}

	const char*	key(void)	const	{ return m_key.c_str(); }	//!< �L�[�̎擾
	const char*	value(void)	const	{ return m_value.c_str(); }	//!< �l�̎擾

private:
	friend class TestResult;
	::std::string m_key;
	::std::string m_value;
};

/**
 * @brief	�e�X�g���ʂ������N���X
*/
class TestResult
{
	typedef ::std::vector<TestPartResult>	TestPartResults;
	typedef ::std::vector<TestProperty>		TestPropertys;
public:
	TestResult(void) {}

public:
	/**
	 * @brief	�����������ǂ���
	 * @return	�^�U�l
	*/
	bool		Passed(void) const		{ return !Failed(); }
	/**
	 * @brief	���s�������ǂ���
	 * @return	�^�U�l
	*/
	bool		Failed(void) const
	{
		for( TestPartResults::const_iterator it=m_test_part_results.begin(), end=m_test_part_results.end(); it != end; ++it )
		{
			if( it->failed() ) return true;
		}
		return false;
	}

	/**
	 * @brief	�v���I�ȃG���[�����邩�ǂ���
	 * @return	�^�U�l
	*/
	bool		HasFatalFailure(void)	const	{ return HasResult(TestPartResult::kFatalFailure); }

	/**
	 * @brief	�v���I�łȂ��G���[�����邩�ǂ���
	 * @return	�^�U�l
	*/
	bool		HasNonfatalFailure(void)	const	{ return HasResult(TestPartResult::kNotFatalFailure); }

	/**
	 * @brief	�e�X�g�̎��s���Ԃ̎擾
	 * @return	�e�X�g�̎��s����
	*/
	TimeInMillisec	elapsed_time(void)		const	{ return m_elapsedmsec; }

	/**
	 * @brief	���ʂ̐����擾
	 * @return	���ʂ̐�
	*/
	int			total_part_count(void)		const	{ return static_cast<int>(m_test_part_results.size()); }

	/**
	 * @brief	�v���p�e�B�����̎擾
	 * @return	����
	*/
	int			test_property_count(void)	const	{ return static_cast<int>(m_test_propertys.size()); }

	/**
	 * @brief	�e�X�g���ʂ̎擾
	 * @param [in]	index	= �C���f�b�N�X
	 * @return	�e�X�g����
	*/
	const TestPartResult&	GetTestPartResult(int index) const	{ return m_test_part_results[index]; }

	/**
	 * @brief	�v���p�e�B�̎擾
	 * @param [in]	index	= �C���f�b�N�X
	 * @return	�v���p�e�B��
	*/
	const TestProperty&		GetTestProperty(int index) const	{ return m_test_propertys[index]; }

public:
	/**
	 * @brief	���s�̐����擾
	 * @return	���s�̐�
	*/
	int			total_error_count(void)		const
	{
		int count = 0;
		for( TestPartResults::const_iterator it=m_test_part_results.begin(), end=m_test_part_results.end(); it != end; ++it )
		{
			if( it->failed() ) ++count;
		}
		return count;
	}

private:
	void AddTestPartResult(const TestPartResult& result)	{ m_test_part_results.push_back(result); }
	void set_elapsed_time(TimeInMillisec time)		{ m_elapsedmsec = time; }

private:
	void RecordProperty(const TestProperty& prop)
	{
		for( TestPropertys::iterator it=m_test_propertys.begin(), end=m_test_propertys.end(); it != end; ++it )
		{
			if( detail::IsStringEqual(it->key(), prop.key()) )
			{
				it->m_value = prop.m_value;
				return;
			}
		}
		m_test_propertys.push_back(prop);
	}

	void ClearResult(void)
	{
		m_test_part_results.clear();
		m_elapsedmsec = 0;
	}
	bool HasResult(TestPartResult::Type eType) const
	{
		for( TestPartResults::const_iterator it=m_test_part_results.begin(), end=m_test_part_results.end(); it != end; ++it )
		{
			if( it->type() == eType ) return true;
		}
		return false;
	}
private:
	friend class TestInfo;
	friend class detail::DefaultGlobalTestPartResultReporter;

	TestPartResults	m_test_part_results;
	TestPropertys	m_test_propertys;
	TimeInMillisec	m_elapsedmsec;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestResult);
};

}	// end of namespace iutest

#endif
