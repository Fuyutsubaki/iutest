//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util.hpp
 * @brief		iris unit test utility �t�@�C��
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
#ifndef INCG_IRIS_iutest_util_HPP_EBAC3846_4D1E_4b32_A85F_6D6A7CCFAF75_
#define INCG_IRIS_iutest_util_HPP_EBAC3846_4D1E_4b32_A85F_6D6A7CCFAF75_

//======================================================================
// include
#include "util/iutest_util_assertion.hpp"
#include "util/iutest_util_output.hpp"
#include "util/iutest_util_quiet_result_printer.hpp"
#include "util/iutest_util_tests.hpp"

/**
 * @brief iutest utility namespace
*/
namespace iuutil {}

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�t�@�C���V�X�e���̐ݒ�
 * @note		���[�U�[��`�̃t�@�C���N���X�𗘗p����悤�ɂ��邽�߂̃}�N���ł��B
*/
#define IUTEST_FILESYSTEM_INSTANTIATE(file_class_name)	IUTEST_FILESYSTEM_INSTANTIATE_(file_class_name)

/**
 * @private
 * @{
*/
#define IUTEST_FILESYSTEM_INSTANTIATE_(file_class_name)	static ::iutest::FileSystem< file_class_name >	s_iutest_filesystem_

/**
 * @}
*/

#endif
