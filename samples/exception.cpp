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
 * 例外アサーション
*//*--------------------------------------------------*/
#if IUTEST_HAS_EXCEPTIONS

static void	ExceptionFunction(int i)
{
	switch( i )
	{
	case 0:
		return;
	case 1:
		throw 2;
	case 2:
		throw ::std::bad_exception();
	case 3:
		throw "error";
	case 4:
		throw ::std::string("error");
	default:
		break;
	}
}

IUTEST(AssertionTest, Exception)
{
	IUTEST_EXPECT_THROW(ExceptionFunction(2), ::std::bad_exception);
	IUTEST_EXPECT_ANY_THROW(ExceptionFunction(1));
	IUTEST_EXPECT_NO_THROW(ExceptionFunction(0));

	IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
	IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 0);

	IUTEST_ASSERT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
	IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
}

class exception_test
{
public:
	exception_test(const ::std::vector<int>&)
	{
		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
	}
};

IUTEST(AssertionTest, Exception2)
{
	::std::vector<int> a;
	IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

/* ---------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if defined(SHOW_FAILURE)	// Failure Test

#if IUTEST_HAS_EXCEPTIONS
IUTEST(TestExpectFailure, Exception)
{
	IUTEST_EXPECT_THROW(ExceptionFunction(0), int);
	IUTEST_EXPECT_ANY_THROW(ExceptionFunction(0));
	IUTEST_EXPECT_NO_THROW(ExceptionFunction(2));
	IUTEST_EXPECT_NO_THROW(throw "error");

	IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 0);
	IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 2);

	IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "Error");
	IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "rror");
}
IUTEST(TestExpectFailure, UnexpectedException1)
{
	throw "fail";
}
IUTEST(TestExpectFailure, UnexpectedException2)
{
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
IUTEST_PRAGMA_GCC_WARN_PUSH()
IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnonnull")

	strcpy(NULL, NULL);

IUTEST_PRAGMA_GCC_WARN_POP()
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
}
#endif

#endif
