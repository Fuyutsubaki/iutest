//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_japanese_tests.cpp
 * @brief		IUTEST_JAPANESE_NAME �Ή��e�X�g
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_TESTNAME_ALIAS

IUTEST_PACKAGE(japanese_test)
{

IUTEST(JapaneseTest, IUTEST_JAPANESE_NAME(����������))
{
//	IUTEST_SUCCEED() << "����������";
	IUTEST_SUCCEED() << ::iutest::UnitTest::GetInstance()->current_test_info()->name();
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST(JapaneseTest, IUTEST_JAPANESE_NAME(����������))
{
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST(IUTEST_JAPANESE_NAME(����������), IUTEST_JAPANESE_NAME(����������))
{
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("japanese_test.����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

class FixedTest : public ::iutest::Test {};

IUTEST_F(IUTEST_JAPANESE_NAME_F(FixedTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("japanese_test.����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

#if IUTEST_HAS_PARAM_TEST
class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(IUTEST_JAPANESE_NAME_F(ParamTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("My1/japanese_test.����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("My1/����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("����������/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_P(IUTEST_JAPANESE_NAME_F(ParamTest, ����������), Japanese)
{
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("My1/japanese_test.����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("My1/����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("Japanese/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, IUTEST_JAPANESE_NAME_F(ParamTest, ����������), ::iutest::Values(0));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE(TypedTest, int);

IUTEST_TYPED_TEST(IUTEST_JAPANESE_NAME_F(TypedTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("japanese_test.����������/0", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("����������/0", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

#endif

#if 0	// ���T�|�[�g
#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE_P(TypeParamTest);

IUTEST_TYPED_TEST_P(TypeParamTest, IUTEST_JAPANESE_NAME_F(aiueo, ����������))
{
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_REGISTER_TYPED_TEST_CASE_P(TypeParamTest, aiueo);

IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(My1, TypeParamTest, int);

#endif

#endif

#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
	IUTEST_ASSERT_EQ(x, y);
#if IUTEST_HAS_PACKAGE
	IUTEST_ASSERT_STREQ("japanese_test.����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#else
	IUTEST_ASSERT_STREQ("����������", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
#endif
	IUTEST_ASSERT_STREQ("�C�R�[��/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}
IUTEST_PMZ(IUTEST_JAPANESE_NAME(����������), IUTEST_JAPANESE_NAME(�C�R�[��), TestFunction, 0, 0);

#endif

#if IUTEST_HAS_IGNORE_TEST

namespace ignore_test
{

IUTEST_IGNORE(IUTEST_JAPANESE_NAME(����������), IUTEST_JAPANESE_NAME(����������))
{
}

IUTEST_F_IGNORE(IUTEST_JAPANESE_NAME_F(FixedTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
}

#if IUTEST_HAS_PARAM_TEST

IUTEST_P_IGNORE(IUTEST_JAPANESE_NAME_F(ParamTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
}

#endif

#if IUTEST_HAS_TYPED_TEST

IUTEST_TYPED_TEST_IGNORE(IUTEST_JAPANESE_NAME_F(TypedTest, ����������), IUTEST_JAPANESE_NAME(����������))
{
}

#endif

}

#endif

}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	
	int ret = IUTEST_RUN_ALL_TESTS();
	if( ret != 0 ) return 1;
#if IUTEST_HAS_TESTNAME_ALIAS
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->total_test_case_count() == 5 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->total_test_count() == 8 );

#endif
	printf("*** Successful ***\n");
	return 0;
}
