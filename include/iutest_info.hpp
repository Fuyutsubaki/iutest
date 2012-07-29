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
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
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
#include "internal/iutest_factory.h"
#include "internal/iutest_exception.h"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	�e�X�g���N���X
*/
class TestInfo : public detail::iu_list_node<TestInfo>
{
private:
	class Mediator : public detail::iuITestInfoMediator
	{
	public:
		Mediator(TestInfo* p=NULL) : iuITestInfoMediator(p) {}
	public:
		virtual	bool	HasFatalFailure(void) const
		{
			return ptr()->HasFatalFailure();
		}
		virtual	bool	HasNonfatalFailure(void) const
		{
			return ptr()->HasNonfatalFailure();
		}
		virtual bool	HasFailure(void) const
		{
			return ptr()->HasFailure();
		}
		virtual void	RecordProperty(const TestProperty& prop)
		{
			return ptr()->RecordProperty(prop);
		}
	public:
		void SetPointer(TestInfo* p) { m_test_info = p; }
	};
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase	= �e�X�g�P�[�X�����
	 * @param [in]	name		= �e�X�g��
	 * @param [in]	factory		= �e�X�g������
	*/
	TestInfo(detail::iuITestCaseMediator* testcase, const char* name, detail::iuFactoryBase* factory)
		: m_testcase(testcase)
		, m_testname(name)
		, m_factory(factory)
		, m_should_run(true)
		, m_disable(false)
	{
		m_mediator.SetPointer(this);
		if( strstr(name, "DISABLED_") == name )
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
	bool			should_run(void)		const	{ return m_should_run; }
	/** is ran */
	bool			is_ran(void)			const	{ return m_ran; }
	/** disable */
	bool			is_disabled_test(void)	const	{ return m_disable; }
	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)		const	{ return m_test_result.elapsed_time(); }
	/** �e�X�g���ʂ̎擾 */
	const TestResult*	result(void)		const	{ return &m_test_result; }

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
	bool	Run(void)
	{
		if( !m_should_run ) return true;

		// �e�X�g�J�n
		TestEnv::event_listeners().OnTestStart(*this);

		RunImpl();

		// �e�X�g�I��
		TestEnv::event_listeners().OnTestEnd(*this);
		return !HasFailure();
	}

private:

	void	RunImpl(void)
	{
		detail::iuStopWatch sw;
		TimeInMillisec elapsedmsec = 0;

		m_ran = true;

#if IUTEST_HAS_EXCEPTIONS
		if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_EACH) )
		{
			detail::auto_ptr<Test> p = m_factory->Create();
			try
			{
				sw.start();
#if IUTEST_HAS_SEH
				RunOnMSC(p);
#else
				p->Run(&m_mediator);
#endif
				elapsedmsec = sw.stop();
			}
			catch (const ::std::exception& e)
			{
				elapsedmsec = sw.stop();
				iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(e.what()), TestPartResult::kFatalFailure).OnFixed(AssertionHelper::Fixed());
				if( TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) ) throw;
			}
			catch (TestPartResult::Type& eType)
			{
				(void)eType;
				elapsedmsec = sw.stop();
				if( TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) ) throw;
			}
			catch (...)
			{
				elapsedmsec = sw.stop();
				iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(NULL), TestPartResult::kFatalFailure).OnFixed(AssertionHelper::Fixed());
				if( TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) ) throw;
			}
		}
		else
#endif
		{
			detail::auto_ptr<Test> p = m_factory->Create();
			sw.start();
			p->Run(&m_mediator);
			elapsedmsec = sw.stop();
		}

		m_test_result.set_elapsed_time(elapsedmsec);

		if( HasFailure() && TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
		{
#if IUTEST_HAS_EXCEPTIONS
			throw HasFatalFailure() ? TestPartResult::kFatalFailure : TestPartResult::kNotFatalFailure;
#else
			exit(1);
#endif
		}
	}

#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
	void	RunOnMSC(detail::auto_ptr<Test>& test)
	{
		_EXCEPTION_POINTERS* info = NULL;
		__try
		{
			test->Run(&m_mediator);
		}
		__except (info = GetExceptionInformation()
			, detail::seh_exception::should_process_through_break_and_cppexceptions(GetExceptionCode()))
		{
			detail::seh_exception::translator(GetExceptionCode(), info);
		}
	}
#endif

	void	RecordProperty(const TestProperty& prop)
	{
		m_test_result.RecordProperty(prop);
	}
private:
	/**
	 * @brief	�e�X�g�̃N���A
	*/
	void	clear(void)
	{
		m_ran = false;
		m_test_result.ClearResult();
	}

	/*
	 * @brief	�e�X�g�̃t�B���^�����O
	 * @return	���s����ꍇ�͐^
	*/
	bool	filter(void)
	{
		bool run = true;
		// �����e�X�g�Ȃ���s���Ȃ�
		if( !TestFlag::IsEnableFlag(TestFlag::RUN_DISABLED_TESTS)
			&& is_disabled_test() )
		{
			run = false;
		}
		if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
		{
			if( !detail::iuRegex::match(TestEnv::test_filter(), test_full_name().c_str()) ) 
			{
				run = false;
			}
		}
		m_should_run = run;
		return m_should_run;
	}

private:
	friend class UnitTestImpl;
	friend class UnitTest;
	friend class TestCase;

	detail::iuITestCaseMediator*	m_testcase;	//!< �e�X�g�P�[�X�����
	::std::string					m_testname;	//!< �e�X�g��
	::std::string			m_value_param;		//!< value param string
	TestResult				m_test_result;		//!< �e�X�g����
	detail::iuFactoryBase*	m_factory;			//!< �e�X�g������
	Mediator				m_mediator;			//!< ���g�̒���C���X�^���X
	bool					m_should_run;		//!< ���s���ׂ����̐^�U�l
	bool					m_ran;				//!< ���s�������ǂ���
	bool					m_disable;			//!< �����^�U�l

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestInfo);
};

}	// end of namespace iutest

#endif
