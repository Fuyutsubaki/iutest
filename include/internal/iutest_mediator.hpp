//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_mediator.hpp
 * @brief		iris unit test ����� �t�@�C��
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
#ifndef INCG_IRIS_iutest_mediator_HPP_BFBE202B_0E60_4e44_8BDA_CB801D264F3E_
#define INCG_IRIS_iutest_mediator_HPP_BFBE202B_0E60_4e44_8BDA_CB801D264F3E_

//======================================================================
// include

namespace iutest {

//======================================================================
// declare
class TestInfo;
class TestCase;
class TestPartResult;

namespace detail
{

//======================================================================
// class
/**
 * @brief	TestInfo ����҃C���^�[�t�F�C�X
*/
class iuITestInfoMediator
{
protected:
	TestInfo*	m_test_info;
public:
	iuITestInfoMediator(TestInfo* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_test_info(p) {}
public:
	virtual	bool	HasFatalFailure(void) const = 0;
	virtual	bool	HasNonfatalFailure(void) const = 0;
	virtual bool	HasFailure(void) const = 0;
	TestInfo*	ptr(void) const IUTEST_CXX_NOEXCEPT_SPEC { return m_test_info; }
};

/**
 * @brief	TestCase ����҃C���^�[�t�F�C�X
*/
class iuITestCaseMediator
{
protected:
	TestCase* m_test_case;
public:
	iuITestCaseMediator(TestCase* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_test_case(p) {}
public:
	virtual const char*	test_case_name(void) const = 0;
	virtual const char*	type_param(void) const = 0;
	TestCase*	ptr(void) const IUTEST_CXX_NOEXCEPT_SPEC { return m_test_case; }
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
