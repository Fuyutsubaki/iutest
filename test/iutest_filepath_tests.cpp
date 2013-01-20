//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_filepath_tests.cpp
 * @brief		iutest filepath test
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
#include "../include/internal/iutest_filepath.hpp"

#if !defined(IUTEST_USE_GTEST)
IUTEST(FilePath, GetExecFilePath)
{
	::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetExecFilePath();
	IUTEST_EXPECT_FALSE(path.IsEmpty());
	IUTEST_EXPECT_TRUE (path.FileOrDirectoryExists());
}
#endif

IUTEST(FilePath, IsDirectory)
{
	::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetCurrentDir();
	IUTEST_EXPECT_FALSE(path.IsEmpty());
	IUTEST_EXPECT_TRUE (path.DirectoryExists());
}

IUTEST(FilePath, RemoveExtension)
{
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension("bin"));
		IUTEST_EXPECT_EQ("test", path.RemoveExtension("exe"));
#if !defined(IUTEST_USE_GTEST)
		IUTEST_EXPECT_EQ("test", path.RemoveExtension());
#endif
	}
	{
		::iutest::internal::FilePath path("test.exe.bin");
		IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension("bin"));
		IUTEST_EXPECT_EQ("test.exe.bin", path.RemoveExtension("exe"));
#if !defined(IUTEST_USE_GTEST)
		IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension());
#endif
	}
}

IUTEST(FilePath, RemoveFileName)
{
#if !defined(IUTEST_USE_GTEST)
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_EXPECT_EQ( ::iutest::internal::FilePath::GetRelativeCurrentDir(), path.RemoveFileName());
	}
	{
		::iutest::internal::FilePath path("test/test.exe");
		// TODO : gtest �̏ꍇ�A���K�����ꂽ�p�X���Ԃ�
		IUTEST_EXPECT_EQ("test/", path.RemoveFileName());
	}
#endif
}

IUTEST(FilePath, RemoveDirectoryName)
{
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_EXPECT_EQ("test.exe", path.RemoveDirectoryName());
	}
	{
		::iutest::internal::FilePath path("test/test.exe");
		IUTEST_EXPECT_EQ("test.exe", path.RemoveDirectoryName());
	}
}

IUTEST(FilePath, PrintTo)
{
	::iutest::internal::FilePath path("test.exe");
	IUTEST_ASSERT_STREQ("test.exe", ::iutest::PrintToString(path));
}

