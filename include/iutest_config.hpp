//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_config.hpp
 * @brief		iris unit test config �t�@�C��
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
#ifndef INCG_IRIS_iutest_config_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_
#define INCG_IRIS_iutest_config_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_

//======================================================================
// include

/**
 * @defgroup	IUTEST_CONFIG	IUTEST_CONFIG
 * @brief		�ݒ�}�N��
 * @note		���[�U�[�����O��`���邱�ƂŕύX�\
 * @{
*/

/**
 * @defgroup	IUTEST_CONFIG_OUTPUT	OUTPUT
 * @brief		�o�͊֌W CONFIG
 * @{
*/

#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)	vprintf(f, a)	//!< vprintf �Ăяo���}�N��
#endif

#ifndef IUTEST_REPORT_SKIPPED
#  define IUTEST_REPORT_SKIPPED		1			//!< xml �o�͂� skipped �^�O���܂߂邩�ǂ���
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_TEST	TEST
 * @brief		�e�X�g�֌W CONFIG
 * @{
*/

#ifndef IUTEST_HAS_PARAM_METHOD_TEST
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_HAS_PARAM_METHOD_TEST	1	//!< �p�����^���C�Y�֐��R�[���e�X�g���g�p�\���ǂ���
#  else
#    define IUTEST_HAS_PARAM_METHOD_TEST	0	//!< �p�����^���C�Y�֐��R�[���e�X�g���g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_PARAM_TEST
#  define IUTEST_HAS_PARAM_TEST		1	//!< �l���p�����[�^�������e�X�g���g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_TYPED_TEST
#  define IUTEST_HAS_TYPED_TEST		1	//!< �^�t���e�X�g���g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_TYPED_TEST_P
//! �^���p�����[�^�������e�X�g���g�p�\���ǂ���
#  if IUTEST_HAS_TYPED_TEST && !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_TYPED_TEST_P	1
#  else
#    define IUTEST_HAS_TYPED_TEST_P	0
#  endif
#endif

#ifndef IUTEST_TYPED_TEST_P_STRICT
#  define IUTEST_TYPED_TEST_P_STRICT	1	//!< ��茵�����\���`�F�b�N���s�����ǂ���
#endif

#if IUTEST_HAS_TYPED_TEST_P
#  if IUTEST_TYPED_TEST_P_STRICT
#    include <set>
#  endif
#endif

#ifndef IUTEST_HAS_COMBINE
//! ::iutest::Combine ���g�p�\���ǂ���
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_COMBINE		1
#  else
#    define IUTEST_HAS_COMBINE		0
#  endif
#endif

#ifndef IUTEST_HAS_PAIRWISE
//! ::iutest::Pairwise ���g�p�\���ǂ���
#  if IUTEST_HAS_COMBINE
#    define IUTEST_HAS_PAIRWISE		1
#  else
#    define IUTEST_HAS_PAIRWISE		0
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_VALUES
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_VALUES	1	//!< �ϒ������ɑΉ����� ::iutest::Values ���g�p�\���ǂ���
#  else
#    define IUTEST_HAS_VARIADIC_VALUES	0	//!< �ϒ������ɑΉ����� ::iutest::Values ���g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_COMBINE
#  if IUTEST_HAS_COMBINE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_COMBINE	1	//!< �ϒ������ɑΉ����� ::iutest::Combine ���g�p�\���ǂ���
#  else
#    define IUTEST_HAS_VARIADIC_COMBINE	0	//!< �ϒ������ɑΉ����� ::iutest::Combine ���g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_PAIRWISE
#  if IUTEST_HAS_PAIRWISE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_PAIRWISE	1	//!< �ϒ������ɑΉ����� ::iutest::Pairwise ���g�p�\���ǂ���
#  else
#    define IUTEST_HAS_VARIADIC_PAIRWISE	0	//!< �ϒ������ɑΉ����� ::iutest::Pairwise ���g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_THROW_ON_ASSERT_FAILURE
/**
 * @brief	ASSERT �}�N���Ŏ��s���ɗ�O�� throw ���܂��B
 * @note	�T�u�֐��ɃA�T�[�V�������L�q���Ă��A���̎��_�Ńe�X�g�����f�����悤�ɂȂ�܂�
*/
#  define IUTEST_THROW_ON_ASSERT_FAILURE	0
#endif

#ifndef IUTEST_HAS_GENRAND
#  define IUTEST_HAS_GENRAND		1	//!< �e�X�g���Ƃ� genrand �֐����g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_PACKAGE
#  define IUTEST_HAS_PACKAGE		1	//!< �p�b�P�[�W�@�\�����邩�ǂ���
#endif

// peep
#ifndef IUTEST_HAS_PEEP
#  define IUTEST_HAS_PEEP			1	//!< private �����o�[�ւ̃A�N�Z�X�}�N�����g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_PEEP_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_FUNC	1	//!< private �����o�[�֐��ւ̃A�N�Z�X���\���ǂ���
#  else
#    define IUTEST_HAS_PEEP_FUNC	0	//!< private �����o�[�֐��ւ̃A�N�Z�X���\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_PEEP_STATIC_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_STATIC_FUNC	1	//!< private static �����o�[�֐��ւ̃A�N�Z�X���\���ǂ���
#  else
#    define IUTEST_HAS_PEEP_STATIC_FUNC	0	//!< private static �����o�[�֐��ւ̃A�N�Z�X���\���ǂ���
#  endif
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_FILE	FILE
 * @brief		�t�@�C���֌W CONFIG
 * @{
*/

// file
#ifndef IUTEST_HAS_FOPEN
#  define IUTEST_HAS_FOPEN			1	//!< fopen ���g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_FILE_STAT
#  define IUTEST_HAS_FILE_STAT		0	//!< stat ���g�p�\���ǂ���
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_TIME	TIME
 * @brief		TIME�֌W CONFIG
 * @{
*/

#ifndef IUTEST_HAS_CTIME
#  if	defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_CTIME		0	//!< time �֐����g�p�\���ǂ���
#  else
#    define IUTEST_HAS_CTIME		1	//!< time �֐����g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_GETTIMEOFDAY
#  define IUTEST_HAS_GETTIMEOFDAY	0	//!< gettimeofday �֐����g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_CLOCK
#  define IUTEST_HAS_CLOCK			0	//!< clock �֐����g�p�\���ǂ���
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_OTHER	OTHER
 * @brief		���̑��� CONFIG
 * @{
*/

// other
#ifndef IUTEST_HAS_STRINGSTREAM
#  define IUTEST_HAS_STRINGSTREAM	1	//!< std::stringstream ���g�p�\���ǂ���
#endif

#ifndef IUTEST_USE_STRSTREAM
#  define IUTEST_USE_STRSTREAM		0	//!< std::strstream ���g�p�\���ǂ���
#endif

/**
 * @}
*/

// Doxygen �p
#ifdef IUTEST_BUILD_DOXYGEN

/**
 * @ingroup	IUTEST_CONFIG_TIME	TIME
 * @{
*/

#define IUTEST_GetMillisec()	//!< ���ݎ����̃~���b�擾�֐���Ǝ���`

/**
* @}
*/


/**
 * @brief	iutest �� t1/tuple.h ���C���N���[�h���邩�ǂ���
 * @details	1: std::tr1 ���O��Ԃɂ��� tuple ���g�p���܂��B
 *			tuple.h �̓��[�U�[���C���N���[�h���܂��B
 *			0: �w��Ȃ� iutest �������Ŕ��f���܂��B
*/
#define IUTEST_USE_EXTERNAL_TR1_TUPLE	0

/**
 * @brief	iutest �� tuple.h ���C���N���[�h���邩�ǂ���
 * @details	1: std ���O��Ԃɂ��� tuple ���g�p���܂��B
 *			tuple.h �̓��[�U�[���C���N���[�h���܂��B
 *			0: �w��Ȃ� iutest �������Ŕ��f���܂��B
*/
#define IUTEST_USE_EXTERNAL_STD_TUPLE	0

/**
 * @ingroup	IUTEST_CONFIG_OTHER	OTHER
 * @{
*/

#define IUTEST_NO_GETENV	//!< getenv �֐����Ȃ��ꍇ�͒�`
#define IUTEST_NO_PUTENV	//!< putenv �֐����Ȃ��ꍇ�͒�`
#define IUTEST_NO_GETCWD	//!< getcwd �֐����Ȃ��ꍇ�͒�`

/**
 * @}
*/

#endif

/**
 * @}
*/

#endif
