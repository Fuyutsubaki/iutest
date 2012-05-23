//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_case.hpp
 * @brief		iris unit test testcase �t�@�C��
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
#ifndef INCG_IRIS_iutest_case_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_iutest_case_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "iutest_info.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	�e�X�g�P�[�X
*/
class TestCase : public detail::iu_list_node<TestCase>
{
protected:
	typedef detail::iu_list<TestInfo>	iuTestInfos;	//!< TestInfo ���X�g
protected:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase_name	= �e�X�g�P�[�X��
	 * @param [in]	id				= �e�X�g�P�[�XID
	 * @param [in]	setup			= �e�X�g���O���s�֐�
	 * @param [in]	teardown		= �e�X�g������s�֐�
	*/
	TestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
	: m_testcase_name(testcase_name)
	, m_setup(setup), m_teardown(teardown)
	, m_id(id), m_disable_num(0)
	, m_should_run_num(0)
	, m_elapsedmsec(0)
	, m_disable(false)
	{
		if( strstr(testcase_name, "DISABLED_") == testcase_name )
		{
			m_disable = true;
		}
	}

public:
	/**
	 * @brief	�f�X�g���N�^
	*/
	virtual	~TestCase(void) {}

public:
	/**
	 * @brief	�e�X�g�̎��s
	 * @return	����
	*/
	bool	Run(void)
	{
		if( !should_run() ) return true;

		if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
		{
			m_testinfos.shuffle(TestEnv::genrand());
		}

		// �e�X�g�J�n
		TestEnv::event_listeners().OnTestCaseStart(*this);
		bool result = RunImpl();
		// �e�X�g�I��
		TestEnv::event_listeners().OnTestCaseEnd(*this);

		return result;
	}

public:
	/** test case ���̎擾 */
	const	char*	name(void)					const	{ return m_testcase_name.c_str(); }
	
	/** �e�X�g���� */
	int				total_test_count(void)		const	{ return m_testinfos.count(); }
	/** ���s�����e�X�g���� */
	int				test_to_run_count(void)		const	{ return m_should_run_num; }
	/** ���s�e�X�g���� */
	int				failed_test_count(void)		const	{ return get_failed_test_count(); }
	/** �����e�X�g���� */
	int				disabled_test_count(void)	const	{ return m_disable_num; }
	/** �����e�X�g���� */
	int				successful_test_count(void)	const	{ return test_to_run_count() - failed_test_count(); }
	/** �X�L�b�v�e�X�g���� */
	int				skip_test_count(void)		const	{ return total_test_count() - test_to_run_count(); }
	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)			const	{ return m_elapsedmsec; }

	/** TestInfo �̎擾 */
	const TestInfo*	GetTestInfo(int index)		const	{ return m_testinfos[index]; }
	/** should_run */
	bool			should_run(void)			const	{ return m_should_run_num != 0; }

	/** �e�X�g�������������ǂ��� */
	bool			Passed(void)				const	{ return get_failed_test_count() == 0; }
	/** �e�X�g�����s�������ǂ��� */
	bool			Failed(void)				const	{ return !Passed(); }

	/** type param ������̎擾 */
	virtual const char*	type_param(void)		const	{ return NULL; }

	/** TestCase �o�͏��̎擾 */
	std::string testcase_name_with_where(void) const
	{
		std::string str = m_testcase_name;
		if( type_param() != NULL )
		{
			str += ", where TypeParam = ";
			str += type_param();
		}
		return str;
	}

private:
	/**
	 * @brief	���s
	 * @return	����
	*/
	bool RunImpl(void)
	{
		bool result=true;
		m_setup();
		m_elapsedmsec = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( it->should_run() )
			{
				// ���s
				if( !it->Run() )
				{
					result = false;
				}
				m_elapsedmsec += it->elapsed_time();
			}
		}
		m_teardown();
		return result;
	}

public:
	/**
	 * @private
	 * @brief	�e�X�g�P�[�X��r�p�I�u�W�F�N�g
	*/
	struct FindOp
	{
		TestTypeId	m_id;
		const char*	m_name;

		bool operator () (const TestCase* p) const
		{
			if( p->get_typeid() == m_id && (strcmp(p->name(), m_name) == 0) )
			{
				return true;
			}
			return false;
		}
	};
private:
	/**
	 * @brief	�e�X�g�̃N���A
	*/
	void	clear(void)
	{
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			it->clear();
		}
	}

	/*
	 * @brief	�e�X�g�̃t�B���^�����O
	 * @return	���s����ꍇ�͐^
	*/
	bool	filter(void)
	{
		m_should_run_num = 0;
		m_disable_num = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( m_disable )
			{
				// DISABLE �̓`��
				it->m_disable = true;
			}
			if( it->is_disabled_test() )
			{
				++m_disable_num;
			}
			if( it->filter() )
			{
				++m_should_run_num;
			}
		}
		return should_run();
	}

	/** ���s�e�X�g���� */
	int get_failed_test_count(void) const
	{
		int count = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( it->should_run() && it->HasFailure() ) ++count;
		}
		return count;
	}

private:
	friend bool	operator == (const TestCase& lhs, const TestCase& rhs)
	{
		return (lhs.m_id == rhs.m_id) && (strcmp(lhs.name(), rhs.name()) == 0);
	}

	void	push_back(TestInfo* p)	{ m_testinfos.push_back(p); }

private:
	iuTestInfos::iterator	begin(void)	const		{ return m_testinfos.begin(); }
	iuTestInfos::iterator	end(void)	const		{ return m_testinfos.end(); }
	TestTypeId				get_typeid(void) const	{ return m_id; }

private:
	friend class UnitTestImpl;
	friend class UnitTest;

	std::string		m_testcase_name;	//!< �e�X�g�P�[�X��
	iuTestInfos		m_testinfos;		//!< �e�X�g��񃊃X�g
	SetUpMethod		m_setup;			//!< SetUp �֐�
	TearDownMethod	m_teardown;			//!< TearDown �֐�
	TestTypeId		m_id;				//!< TypeID
	int				m_disable_num;		//!< ���������e�X�g�̑���
	int				m_should_run_num;	//!< ���s���ׂ��e�X�g�̑���
	TimeInMillisec	m_elapsedmsec;		//!< �e�X�g����
	bool			m_disable;			//!< �����^�U�l

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestCase);
};

/**
 * @brief	�^���e�X�g�P�[�X
*/
template<typename T>
class TypedTestCase : public TestCase
{
public:
	typedef T	TypeParam;	//!< �^

protected:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase_name	= �e�X�g�P�[�X��
	 * @param [in]	id				= �e�X�g�P�[�XID
	 * @param [in]	setup			= �e�X�g���O���s�֐�
	 * @param [in]	teardown		= �e�X�g������s�֐�
	*/
	TypedTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: TestCase(testcase_name, id, setup, teardown)
#if IUTEST_HAS_RTTI
		, m_type_param(typeid(TypeParam).name())
#endif
	{}

public:
	/** type param ������̎擾 */
	virtual const char*	type_param(void) const	{ return m_type_param.empty() ? NULL : m_type_param.c_str(); }

private:
	friend class UnitTestImpl;

	std::string	m_type_param;		//!< type param string
};

namespace detail
{

/**
 * @brief	�e�X�g�P�[�X�����
*/
class TestCaseMediator : public detail::iuITestCaseMediator
{
public:
	TestCaseMediator(TestCase* p) : iuITestCaseMediator(p) {}
public:
	virtual const char*	test_case_name(void) const { return m_test_case->name(); }
	virtual const char*	type_param(void) const	{ return m_test_case->type_param(); }
};

}	// end of namespace detail

}	// end of namespace iutest

#endif
