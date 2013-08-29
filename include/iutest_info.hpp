//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_info.hpp
 * @brief		iris unit test ��� �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_info_HPP_764A79A8_E822_4c0f_8CB7_82C635BA28BA_
#define INCG_IRIS_iutest_info_HPP_764A79A8_E822_4c0f_8CB7_82C635BA28BA_

//======================================================================
// include
#include "iutest_body.hpp"
#include "internal/iutest_factory.hpp"
#include "internal/iutest_exception.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	�e�X�g���N���X
*/
class TestInfo 
	: public detail::iu_list_node<TestInfo>
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase	= �e�X�g�P�[�X�����
	 * @param [in]	name		= �e�X�g��
	 * @param [in]	factory		= �e�X�g������
	*/
	TestInfo(detail::iuITestCaseMediator* testcase, const char* name, detail::iuFactoryBase* factory)
		: m_testname(name)
		, m_factory(factory)
		, m_testcase(testcase)
		, m_should_run(true)
		, m_ran(false)
		, m_disable(false)
		, m_skip(false)
		, m_matches_filter(true)
	{
		m_mediator.SetPointer(this);
		if( detail::IsStringForwardMatching(name, "DISABLED_") )
		{
			m_disable = true;
		}
	}

public:
	/** test case ���̎擾 */
	const	char*	test_case_name(void)	const	{ return m_testcase->test_case_name(); }
	/** test ���̎擾 */
	const	char*	name(void)				const	{ return m_testname.c_str(); }
	/** should_run */
	bool			should_run(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_should_run; }
	/** is ran */
	bool			is_ran(void)			const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_ran; }
	/** disable */
	bool			is_disabled_test(void)	const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_disable; }
	/** is skipped */
	bool			is_skipped(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_skip || m_test_result.Skipped(); }
	/** is reportable */
	bool			is_reportable(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_matches_filter; }
	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)		const	{ return m_test_result.elapsed_time(); }
	/** �e�X�g���ʂ̎擾 */
	const TestResult*	result(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return &m_test_result; }

	/** value param ������̎擾 */
	const	char*	value_param(void)		const	{ return m_value_param.empty() ? NULL : m_value_param.c_str(); }
	/** type param ������̎擾 */
	const	char*	type_param(void)		const	{ return m_testcase->type_param(); }

public:
	/**
	 * @brief	�v���I�ȃG���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	bool	HasFatalFailure(void) const
	{
		return m_test_result.HasFatalFailure();
	}

	/**
	 * @brief	�v���I�ł͂Ȃ��G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	bool	HasNonfatalFailure(void) const
	{
		return m_test_result.HasNonfatalFailure();
	}

	/**
	 * @brief	�G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	bool	HasFailure(void) const
	{
		return m_test_result.Failed();
	}

	/**
	 * @brief	�����������ǂ���
	 * @return	�^�U�l
	*/
	bool	Passed(void) const
	{
		if( is_skipped() ) return false;
		return m_test_result.Passed();
	}

public:
	/** �e�X�g�̃t�������擾 */
	::std::string	test_full_name(void)		const
	{
		::std::string fullname = test_case_name();
		fullname += ".";
		fullname += name();
		return fullname;
	}

	/** �e�X�g�� + where �̎擾 */
	::std::string test_name_with_where(void)	const
	{
		::std::string str = m_testname;
		if( value_param() != NULL )
		{
			str += ", where GetParam() = ";
			str += m_value_param;
		}
		return str;
	}

public:
	/** @private */
	void	set_value_param(const char* str)	{ m_value_param = str; }

private:
	/**
	 * @brief	���s
	*/
	bool	Run(void);

private:

	void	RunImpl(void);

#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
#if IUTEST_HAS_MINIDUMP
	void	MiniDump(_EXCEPTION_POINTERS* ep);
#endif
	void	RunOnMSC(detail::auto_ptr<Test>& test);
#endif

private:
	/**
	 * @brief	�e�X�g�̃N���A
	*/
	void	clear(void);

	/*
	 * @brief	�e�X�g�̃t�B���^�����O
	 * @return	���s����ꍇ�͐^
	*/
	bool	filter(void);

private:
	class Mediator : public detail::iuITestInfoMediator
	{
	public:
		Mediator(TestInfo* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : iuITestInfoMediator(p) {}
	public:
		virtual	bool	HasFatalFailure(void) const IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
		{
			return ptr()->HasFatalFailure();
		}
		virtual	bool	HasNonfatalFailure(void) const IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
		{
			return ptr()->HasNonfatalFailure();
		}
		virtual bool	HasFailure(void) const IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
		{
			return ptr()->HasFailure();
		}
	public:
		void SetPointer(TestInfo* p) { m_test_info = p; }
	};
private:
	friend class UnitTestImpl;
	friend class UnitTest;
	friend class TestCase;

	::std::string			m_testname;			//!< �e�X�g��
	::std::string			m_value_param;		//!< value param string
	TestResult				m_test_result;		//!< �e�X�g����
	Mediator				m_mediator;			//!< ���g�̒���C���X�^���X
	detail::iuFactoryBase*			m_factory;	//!< �e�X�g������
	detail::iuITestCaseMediator*	m_testcase;	//!< �e�X�g�P�[�X�����
	bool					m_should_run;		//!< ���s���ׂ����̐^�U�l
	bool					m_ran;				//!< ���s�������ǂ���
	bool					m_disable;			//!< �����^�U�l
	bool					m_skip;				//!< �X�L�b�v�������ǂ���
	bool					m_matches_filter;	//!< �t�B���^�[�Ƀ}�b�`�������ǂ���

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestInfo);
};

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_info.ipp"
#endif

#endif
