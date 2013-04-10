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
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
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
	TestCase*	AddTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown
		IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T)
		)
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
	void AddTestInfo(TestCase* pCase, TestInfo* pInfo);
	/** @private */
	static void SkipTest(void);

protected:
	/**
	 * @brief	�e�X�g�̃��X�g�A�b�v
	*/
	int		Listup(void) const;

	/**
	 * @brief	�e�X�g�̃��X�g�A�b�v(with where)
	*/
	int		ListupWithWhere(void) const;

	/**
	 * @brief	���O����
	*/
	bool	PreRunner(void);

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

#if IUTEST_HAS_EXCEPTIONS && (defined(_MSC_VER) && (_MSC_VER >= 1400)) && !defined(IUTEST_OS_WINDOWS_MOBILE)
		_set_invalid_parameter_handler(OnInvalidParameter);
#endif
	}
	/**
	 * @brief	��Еt��
	*/
	void	TerminateImpl(void);

private:
#if IUTEST_HAS_EXCEPTIONS && (defined(_MSC_VER) && (_MSC_VER >= 1400)) && !defined(IUTEST_OS_WINDOWS_MOBILE)

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

	// _invalid_parameter_handler
	static void OnInvalidParameter(const wchar_t * expression, const wchar_t * function
		, const wchar_t * file, unsigned int line, uintptr_t pReserved);

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
::std::string MakeIndexTestName(const char* basename, int index);

/**
 * @brief	�e�X�g���̍쐬
 * @param [in]	basename	= �x�[�X��
 * @param [in]	index		= �C���f�b�N�X
*/
template<typename T>
::std::string MakeIndexTypedTestName(const char* basename, int index)
{
#if IUTEST_HAS_RTTI
	::std::string name = basename;
	iuStringStream::type strm; strm << index;
	name += "/";
	name += GetTypeName<T>();
	return name;
#else
	return MakeIndexTestName(basename, index);
#endif
}

/**
 * @brief	�e�X�g���̍쐬
 * @param [in]	prefix		= prefix
 * @param [in]	basename	= �x�[�X��
 * @param [in]	index		= �C���f�b�N�X
*/
::std::string MakePrefixedIndexTestName(const char* prefix, const char* basename, int index);

/**
 * @brief	�e�X�g���̍쐬
 * @param [in]	prefix		= prefix
 * @param [in]	basename	= �x�[�X��
 * @param [in]	index		= �C���f�b�N�X
*/
template<typename T>
::std::string MakePrefixedIndexTypedTestName(const char* prefix, const char* basename, int index)
{
#if IUTEST_HAS_RTTI
	::std::string name = prefix;
	if( !name.empty() ) name += "/";
	name += MakeIndexTypedTestName<T>(basename, index);
	return name;
#else
	return MakePrefixedIndexTestName(prefix, basename, index);
#endif
}

}	// end of namespace detail

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_core_impl.ipp"
#endif

#endif
