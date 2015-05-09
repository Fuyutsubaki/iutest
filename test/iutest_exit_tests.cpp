﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_exit_tests.cpp
 * @brief		exit 対応テスト
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_QUICK_EXIT

class ExitCheckEventListener : public ::iutest::EmptyTestEventListener
{
	virtual void OnTestProgramEnd(const ::iutest::UnitTest& test) IUTEST_CXX_OVERRIDE
	{
		if( test.current_test_info() == NULL ) throw "current_test_info() == NULL";
		if( test.current_test_case() == NULL ) throw "current_test_case() == NULL";
		if( !test.current_test_info()->is_ran() ) throw "is_ran()";
		if( !test.current_test_info()->HasFailure() ) throw "HasFailure()";
	}
};

IUTEST(ExitTest, QuickExit)
{
	::std::quick_exit(0);
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IUTEST_HAS_QUICK_EXIT
	::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
	listeners.Append(new ExitCheckEventListener());

	IUTEST_INIT(&argc, argv);
	IUTEST_RUN_ALL_TESTS();
	return 1;
#else
	(void)argc;
	(void)argv;
	printf("*** IUTEST_HAS_QUICK_EXIT=0 ***\n");
	return 0;
#endif
}
