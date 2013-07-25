//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_env_var_tests.cpp
 * @brief		���ϐ��Ή��e�X�g
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if	defined(USE_GTEST_PREFIX) || defined(IUTEST_USE_GTEST)
#  define ENV_PREFIX	"GTEST_"
#else
#  define ENV_PREFIX	"IUTEST_"
#endif

int SetUpEnvironment(void)
{
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "SHUFFLE=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "RANDOM_SEED=200") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "ALSO_RUN_DISABLED_TESTS=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "BREAK_ON_FAILURE=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "THROW_ON_FAILURE=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "CATCH_EXCEPTIONS=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "PRINT_TIME=1") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "REPEAT=2") == -1 ) return -1;
	if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "FILTER=Flag*") == -1 ) return -1;
	
	if( ::iutest::internal::posix::PutEnv("IUTEST_FILE_LOCATION=vs") == -1 ) return -1;
	return 0;
}

static volatile int g_dummy = SetUpEnvironment();

IUTEST(FlagTest, Check)
{
	if( g_dummy != 0 ) return;	// putenv �Ɏ��s�����ꍇ�̓e�X�g���Ȃ�
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(break_on_failure) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(throw_on_failure) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(catch_exceptions) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(print_time) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(shuffle) );
#if !defined(IUTEST_USE_GTEST)
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(file_location_style_msvc) );
#endif
	
	IUTEST_EXPECT_EQ( 200u, ::iutest::IUTEST_FLAG(random_seed) );
	IUTEST_EXPECT_EQ(   2 , ::iutest::IUTEST_FLAG(repeat) );
	
	IUTEST_EXPECT_STREQ( "Flag*", ::iutest::IUTEST_FLAG(filter).c_str() );
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

