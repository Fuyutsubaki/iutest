﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		parameterized.cpp
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
 * 値をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_TEST
// Param Test Range
class TestP : public ::iutest::TestWithParam<int>
{
protected:
	static int a;
	static int b;
public:
	static void SetUpTestCase(void)
	{
		a = 0;
		b = 0;
	}
};
int TestP::a = 0;
int TestP::b = 0;

IUTEST_INSTANTIATE_TEST_CASE_P(TestPInstance, TestP, ::iutest::Range<int>(0, 10));

#if IUTEST_HAS_CONCAT
IUTEST_INSTANTIATE_TEST_CASE_P(TestPInstance2, TestP, ::iutest::Concat( ::iutest::Bool(), ::iutest::Range(2, 4)));
#endif

IUTEST_P(TestP, TestA)
{
	IUTEST_ASSERT_EQ(a, GetParam());
	++a;
}

IUTEST_P(TestP, TestB)
{
	IUTEST_ASSERT_EQ(b, GetParam());
	++b;
}

// Param Test Bool
class TestBool : public ::iutest::TestWithParam<bool> {};
IUTEST_INSTANTIATE_TEST_CASE_P(TestBoolInstance, TestBool, ::iutest::Bool());

IUTEST_P(TestBool, TestA)
{
	static bool x=false;
	IUTEST_ASSERT_EQ(x, GetParam());
	x = !x;
}

// Param Test ValueIn
const char ValueInTestText[] = "ValueInTestText";
class TestPValueIn : public ::iutest::TestWithParam<char>
{
protected:
	static int a;
public:
	static void SetUpTestCase(void)
	{
		a = 0;
	}
};
int TestPValueIn::a = 0;
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValueInInstance, TestPValueIn, ::iutest::ValuesIn(ValueInTestText));

IUTEST_P(TestPValueIn, TestA)
{
	IUTEST_ASSERT_EQ(ValueInTestText[a++], GetParam());
}

// Param Test Values
class TestPValues1 : public ::iutest::TestWithParam<float> {};
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValues1Instance, TestPValues1, ::iutest::Values(1.0f));

IUTEST_P(TestPValues1, TestA)
{
	IUTEST_ASSERT_FLOAT_EQ(1.0f, GetParam());
}

class TestPValuesN : public ::iutest::TestWithParam<int>
{
protected:
	static int a;
public:
	static void SetUpTestCase(void)
	{
		a = 1;
	}
};
int TestPValuesN::a = 1;
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValuesNInstance, TestPValuesN, ::iutest::Values(1, 2, 3, 4, 5, 6, 7, 8, 9
																	//, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
																	//, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
																	//, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
																	//, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
																	//, 50
																	));

IUTEST_P(TestPValuesN, TestA)
{
	IUTEST_ASSERT_EQ(a++, GetParam());
}

#if IUTEST_HAS_IF_EXISTS && !defined(IUTEST_USE_GTEST)
IUTEST_P(TestPAutoAny, Test)
{
	IUTEST_ASSERT_EQ(1, GetParam<int>());
}

IUTEST_INSTANTIATE_TEST_CASE_P(TestPValuesNInstance, TestPAutoAny, ::iutest::Values(1));
#endif

#if IUTEST_HAS_COMBINE

class TestPCombine : public ::iutest::TestWithParam< ::iutest::tuples::tuple<bool, int, int> >
{
};

IUTEST_P(TestPCombine, TestA)
{
	bool b = ::iutest::tuples::get<0>(GetParam());
	int i1 = ::iutest::tuples::get<1>(GetParam());
	int i2 = ::iutest::tuples::get<2>(GetParam());
	IUTEST_SUCCEED() << b << ", " << i1 << ", " << i2;
}

IUTEST_INSTANTIATE_TEST_CASE_P(TestPCombineInstance, TestPCombine
							   , ::iutest::Combine( ::iutest::Bool(), ::iutest::Values(1, 2), ::iutest::Values(10, 11) ) );
#endif

#if IUTEST_HAS_INITIALIZER_LIST && !defined(IUTEST_USE_GTEST)

class InitializerListValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(InitializerListValuesTest, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_INSTANTIATE_TEST_CASE_P(A, InitializerListValuesTest, ::iutest::ValuesIn({1, 9, 8, 6, 3, 9}));

#endif

#if IUTEST_HAS_RANDOMVALUES

class RandomValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(RandomValuesTest, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_INSTANTIATE_TEST_CASE_P(A, RandomValuesTest, ::iutest::RandomValues(5));

#endif

#endif

/* ---------------------------------------------------
 * パラメタライズ関数コール
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
	IUTEST_ASSERT_EQ(x, y);
}
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 0, 0);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 1, 1);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 2, 2);

class ParamMethodTestFixed : public ::iutest::Test {};

IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 2, 2);

#endif

/* ---------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if defined(SHOW_FAILURE)	// Failure Test

/* ---------------------------------------------------
 * パラメタライズ関数コール
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_METHOD_TEST

IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 0, 0);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 1, 2);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 2, 2);

typedef ParamMethodTestFixed TestFailureParamMethodFixed;

IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 2, 3);

#endif

#endif
