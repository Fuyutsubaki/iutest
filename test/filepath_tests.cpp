﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        filepath_tests.cpp
 * @brief       iutest filepath test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/internal/iutest_filepath.hpp"

IUTEST(FilePath, Empty)
{
    ::iutest::internal::FilePath path;
    IUTEST_EXPECT_TRUE(path.IsEmpty());
}

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_FILE_STAT
IUTEST(FilePath, GetExecFilePath)
{
    ::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetExecFilePath();
    if(!path.IsEmpty())
    {
        IUTEST_EXPECT_TRUE(path.FileOrDirectoryExists()) << path;
    }
}
#endif

#if defined(IUTEST_USE_GTEST) || IUTEST_HAS_FILE_STAT

IUTEST(FilePath, IsDirectory)
{
    ::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetCurrentDir();
    IUTEST_EXPECT_FALSE(path.IsEmpty());
    IUTEST_EXPECT_TRUE (path.DirectoryExists());
}

#endif

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
    {
        ::iutest::internal::FilePath path("test");
        IUTEST_EXPECT_EQ("test", path.RemoveExtension("test"));
        IUTEST_EXPECT_EQ("test", path.RemoveExtension("exe"));
    }
}

IUTEST(FilePath, RemoveFileName)
{
#if !defined(IUTEST_USE_GTEST)
    {
        ::iutest::internal::FilePath path("test.exe");
        IUTEST_EXPECT_EQ( ::iutest::internal::FilePath::GetRelativeCurrentDir(), path.RemoveFileName());
    }
#endif
    {
        ::iutest::internal::FilePath path("test/test.exe");
#ifdef IUTEST_OS_WINDOWS
        const char expected[] = "test\\";
#else
        const char expected[] = "test/";
#endif
        IUTEST_EXPECT_EQ(expected, path.RemoveFileName());
    }
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

#if IUTEST_HAS_PRINT_TO

IUTEST(FilePath, PrintTo)
{
    ::iutest::internal::FilePath path("test.exe");
    IUTEST_ASSERT_STREQ("test.exe", ::iutest::PrintToString(path));
}

#endif
