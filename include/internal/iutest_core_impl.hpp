//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_core_impl.hpp
 * @brief		iris unit test UnitTest ���� �t�@�C��
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
#ifndef INCG_IRIS_iutest_core_impl_HPP_D5ABC7DE_C751_4ac0_922F_547880163891_
#define INCG_IRIS_iutest_core_impl_HPP_D5ABC7DE_C751_4ac0_922F_547880163891_

//======================================================================
// include
#include "iutest_internal.hpp"
#include "iutest_option_message.hpp"
#include "../iutest_case.hpp"

namespace iutest
{

//======================================================================
// class
class UnitTestImpl
{
protected:
	typedef detail::iu_list<TestCase>	iuTestCases;
	//typedef ::std::vector<TestCase*>	iuTestCases;
	typedef ::std::vector<Environment*>	iuEnvironmentList;
protected:
	UnitTestImpl(void) : m_total_test_num(0), m_disable_num(0), m_should_run_num(0)
		, m_elapsedmsec(0)
	{
		ptr() = this;
	}
	~UnitTestImpl(void) { TerminateImpl(); }

public:
	/**
	 * @brief	�e�X�g���̃e�X�g�� TestResult �̎擾
	*/
	static TestResult*	current_test_result(void)
	{
		return Test::GetCurrentTestInfo() ? &(Test::GetCurrentTest()->m_test_info->ptr()->m_test_result) : &ptr()->m_ad_hoc_testresult;
	}

public:
	/** @private */
	template<typename T>
	TestCase*	AddTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
	{
		TestCase::FindOp func = { id, testcase_name };
		iuTestCases& list = m_testcases;
		TestCase* p = detail::FindList(list, func);
		if( p == NULL )
		{
			p = new T (testcase_name, id, setup, teardown);
			list.push_back(p);
		}
		return p;
	}
	/** @private */
	void AddTestInfo(TestCase* pCase, TestInfo* pInfo)
	{
		++m_total_test_num;
		pCase->push_back(pInfo);
	}
	/** @private */
	static void SkipTest(void)
	{
		Test* test = Test::GetCurrentTest();
		if( test != NULL && test->m_test_info->ptr() != NULL )
		{
			test->m_test_info->ptr()->m_skip = true;
		}
	}
protected:
	/**
	 * @brief	�e�X�g�̃��X�g�A�b�v
	*/
	int		Listup(void) const
	{
		detail::iuConsole::output("%d tests from %d testcase\n", m_total_test_num, m_testcases.size() );
		for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			detail::iuConsole::output((*it)->name());
			detail::iuConsole::output("\n");

			for( TestCase::iuTestInfos::const_iterator it2 = (*it)->begin(), end2=(*it)->end(); it2 != end2; ++it2 )
			{
				detail::iuConsole::output("  ");
				detail::iuConsole::output((*it2)->name());
				detail::iuConsole::output("\n");
			}
		}
		return 0;
	}
	/**
	 * @brief	���O����
	*/
	bool	PreRunner(void)
	{
		InitializeImpl();

		if( TestFlag::IsEnableFlag(TestFlag::SHOW_HELP) )
		{
			detail::iuOptionMessage::ShowHelp();
		}
		else if( TestFlag::IsEnableFlag(TestFlag::SHOW_VERSION) )
		{
			detail::iuOptionMessage::ShowVersion();
		}
		else if( TestFlag::IsEnableFlag(TestFlag::SHOW_FEATURE) )
		{
			detail::iuOptionMessage::ShowFeature();
		}
		else if( TestFlag::IsEnableFlag(TestFlag::SHOW_TESTS_LIST) )
		{
			Listup();
		}
		else
		{
			return true;
		}
		return false;
	}

private:
	/**
	 * @brief	�Z�b�g�A�b�v
	*/
	void	InitializeImpl(void)
	{
#if IUTEST_HAS_SEH

#if !defined(IUTEST_OS_WINDOWS_MOBILE)
		SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif

#if	(defined(_MSC_VER) || IUTEST_OS_WINDOWS_MINGW) && !defined(IUTEST_OS_WINDOWS_MOBILE)
		_set_error_mode(_OUT_TO_STDERR);
#endif

#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400 && !defined(IUTEST_OS_WINDOWS_MOBILE)
		if( !TestFlag::IsEnableFlag(TestFlag::BREAK_ON_FAILURE) )
		{
			_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
		}
#endif

#if (IUTEST_HAS_EXCEPTIONS && defined(_MSC_VER))  && !defined(IUTEST_OS_WINDOWS_MOBILE)
		_set_invalid_parameter_handler(OnInvalidParameter);
#endif
	}
	/**
	 * @brief	��Еt��
	*/
	void	TerminateImpl(void)
	{
		for( iuTestCases::iterator it = m_testcases.begin(); it != m_testcases.end(); it = m_testcases.begin())
		{
			TestCase* p = (*it);
			m_testcases.erase(it);
			delete p;
		}
	}

private:
#if (IUTEST_HAS_EXCEPTIONS && defined(_MSC_VER)) && !defined(IUTEST_OS_WINDOWS_MOBILE)

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

	// _invalid_parameter_handler
	static void OnInvalidParameter(const wchar_t * expression, const wchar_t * function
		, const wchar_t * file, unsigned int line, uintptr_t pReserved)
	{
		IUTEST_UNUSED_VAR(file);
		IUTEST_UNUSED_VAR(line);
		IUTEST_UNUSED_VAR(pReserved);
		char func[260];
		wcstombs(func, function, 260);
		char expr[260];
		wcstombs(expr, expression, 260);
		std::string msg = func;
		msg += expr;
		throw std::invalid_argument(msg);
	}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#endif

private:
	static UnitTestImpl*& ptr(void)
	{
		static UnitTestImpl* ptr = NULL;
		return ptr;
	}
protected:
	friend class UnitTestSource;

	int				m_total_test_num;	//!< �o�^���ꂽ�e�X�g����
	int				m_disable_num;		//!< ���������e�X�g����
	int				m_should_run_num;	//!< ���s���ׂ��e�X�g����
	TimeInMillisec	m_elapsedmsec;		//!< �e�X�g�̎��s����
	iuTestCases		m_testcases;		//!< �e�X�g�P�[�X���X�g
	TestResult		m_ad_hoc_testresult;	//!< �e�X�g�����s���łȂ��Ƃ��̃��U���g
};

namespace detail
{

/**
 * @brief	�e�X�g���̍쐬
 * @param [in]	basename	= �x�[�X��
 * @param [in]	index		= �C���f�b�N�X
*/
inline ::std::string MakeIndexTestName(const char* basename, int index)
{
	::std::string name = basename;
	iuStringStream::type strm; strm << index;
	name += "/";
	name += strm.str();
	return name;
}

/**
 * @brief	�e�X�g���̍쐬
 * @param [in]	prefix		= prefix
 * @param [in]	basename	= �x�[�X��
 * @param [in]	index		= �C���f�b�N�X
*/
inline ::std::string MakeIndexTestName(const char* prefix, const char* basename, int index)
{
	::std::string name = prefix;
	if( !name.empty() ) name += "/";
	name += MakeIndexTestName(basename, index);
	return name;
}

}

}	// end of namespace iutest

#endif
