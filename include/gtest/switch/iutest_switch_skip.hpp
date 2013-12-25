//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_switch_skip.hpp
 * @brief		IUTEST_SKIP �؂�ւ���` �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
#define INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define

#else	// !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#ifdef INCG_IRIS_IUTEST_HPP_

#undef IUTEST_SKIP

#endif

//======================================================================
// define
#define IUTEST_SKIP()			GTEST_AMBIGUOUS_ELSE_BLOCKER_	\
								if( ::testing::internal::AlwaysTrue() ) return GTEST_MESSAGE_("Skipped. ", ::testing::TestPartResult::kSuccess)


#endif	// !defined(IUTEST_USE_GTEST)

#endif	// INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
