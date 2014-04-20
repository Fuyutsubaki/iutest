﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		exception.cpp
 * @brief		sample
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * Diabled テスト
*//*--------------------------------------------------*/
// このテストは無効テスト
IUTEST(TestDisabled, DISABLED_Test1)
{
	IUTEST_ASSERT_TRUE(false);
}

IUTEST(TestDisabled, Test2)
{
	IUTEST_ASSERT_TRUE(true);
}

// テストケースすべてを無効にする
IUTEST(DISABLED_TestCaseDisabled, Test1)
{
	IUTEST_ASSERT_TRUE(false);
}
IUTEST(DISABLED_TestCaseDisabled, Test2)
{
	IUTEST_ASSERT_TRUE(false);
}


// DISABLED Test Tips.
#define DISABLED_MacroTest	EnabledTest
#define MacroTest			DISABLED_Test

IUTEST(DISABLED_MacroTest, Enable)
{
	IUTEST_ASSERT_EQ(0, 0);
}

IUTEST(EnabledTest, Count)
{
	const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->current_test_case();
	IUTEST_ASSERT_NOTNULL(testcase);
	IUTEST_ASSERT_EQ(2, testcase->total_test_count());
	IUTEST_ASSERT_EQ(2, testcase->test_to_run_count());
	IUTEST_ASSERT_EQ(0, testcase->disabled_test_count());
	IUTEST_ASSERT_TRUE(testcase->Passed());
	IUTEST_ASSERT_FALSE(testcase->Failed());
}

IUTEST(MacroTest, NotRun)
{
	IUTEST_ASSERT_EQ(2, 3);
}

class EnabledTestFixed : public ::iutest::Test {};

typedef EnabledTestFixed	DISABLED_TestFixed;

#define MacroTestF	DISABLED_TestFixed
#define DISABLED_MacroTestF	EnabledTestFixed

IUTEST_F(MacroTestF, NotRun)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST_F(DISABLED_MacroTestF, Run)
{
	IUTEST_ASSERT_EQ(0, 0);
}

IUTEST_F(EnabledTestFixed, Count)
{
	const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->current_test_case();
	IUTEST_ASSERT_NOTNULL(testcase);
	IUTEST_ASSERT_EQ(2, testcase->total_test_count());
	IUTEST_ASSERT_EQ(2, testcase->test_to_run_count());
	IUTEST_ASSERT_EQ(0, testcase->disabled_test_count());
	IUTEST_ASSERT_TRUE(testcase->Passed());
	IUTEST_ASSERT_FALSE(testcase->Failed());
}
