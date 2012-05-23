//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_spi_switch.hpp
 * @brief		gtest ���� iutest �ւ̐؂�ւ��p �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_spi_switch_HPP_673AE7AC_6F80_4be0_9209_581E3A568525_
#define INCG_IRIS_iutest_spi_switch_HPP_673AE7AC_6F80_4be0_9209_581E3A568525_

#include "iutest_switch.hpp"

#if !defined(IUTEST_USE_GTEST)

#include "../iutest_spi.hpp"

#ifdef GTEST_INCLUDE_GTEST_GTEST_SPI_H_
#undef EXPECT_FATAL_FAILURE
#undef EXPECT_FATAL_FAILURE_ON_ALL_THREADS
#undef EXPECT_NONFATAL_FAILURE
#undef EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS
#endif

#define EXPECT_FATAL_FAILURE					IUTEST_EXPECT_FATAL_FAILURE	
#define EXPECT_FATAL_FAILURE_ON_ALL_THREADS		IUTEST_EXPECT_FATAL_FAILURE
#define EXPECT_NONFATAL_FAILURE					IUTEST_EXPECT_NONFATAL_FAILURE
#define EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS	IUTEST_EXPECT_NONFATAL_FAILURE

#else

#include <gtest/gtest-spi.h>

#ifdef _MSC_VER
// /ZI �I�v�V�������� __LINE__ �� __LINE__Var+N(N�͔ԍ�) �ɂȂ�R���p�C���G���[�ɂȂ邽�߂̑Ή�
#  ifndef __LINE__Var
#    define __LINE__Var	0
#  endif
#endif

#ifdef INCG_IRIS_iutest_spi_HPP_
#undef IUTEST_ASSERT_FATAL_FAILURE
#undef IUTEST_EXPECT_FATAL_FAILURE
#undef IUTEST_ASSERT_NONFATAL_FAILURE
#undef IUTEST_EXPECT_NONFATAL_FAILURE
#endif

#define IUTEST_ASSERT_FATAL_FAILURE				EXPECT_FATAL_FAILURE	
#define IUTEST_EXPECT_FATAL_FAILURE				EXPECT_FATAL_FAILURE
#define IUTEST_ASSERT_NONFATAL_FAILURE			EXPECT_NONFATAL_FAILURE
#define IUTEST_EXPECT_NONFATAL_FAILURE			EXPECT_NONFATAL_FAILURE

#endif

#endif
