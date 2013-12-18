//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_ignore.hpp
 * @brief		iris unit test ignore test �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_
#define INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_

//======================================================================
// define

#if IUTEST_HAS_IGNORE_TEST

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TEST_IGNORE(testcase_, testname_)
 * @brief	�e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_TEST_IGNORE(testcase_, testname_)	IUTEST_TEST_IGNORE_(testcase_, testname_, ::iutest::Test	\
														, ::iutest::internal::GetTestTypeId())

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TEST_IGNORE(testcase_, testname_)
 * @brief	�e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_IGNORE(testcase_, testname_)			IUTEST_TEST_IGNORE(testcase_, testname_)


/**
 * @ingroup	TESTDEF
 * @def		IUTEST_F_IGNORE(testfixture_, testname_)
 * @brief	���[�U�[�w��e�X�g�֐���`�}�N��
 * @param	testfixture_	= �e�X�g�t�B�N�X�`����
 * @param	testname_		= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_F_IGNORE(testfixture_, testname_)	IUTEST_TEST_F_IGNORE_(testfixture_, testname_)

#if IUTEST_HAS_PARAM_TEST

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_P_IGNORE(testcase_, testname_)
 * @brief	�p�����[�^���[�U�[�w��e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_P_IGNORE(testcase_, testname_)				IIUT_TEST_P_IGNORE_(testcase_, testname_)

#endif

#if IUTEST_HAS_TYPED_TEST

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST(testcase_, testname_)
 * @brief	�^�t���e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_TYPED_TEST_IGNORE(testcase_, testname_)		IIUT_TYPED_TEST_IGNORE_(testcase_, testname_)

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST_P(testcase_, testname_)
 * @brief	�^�p�����[�^�e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	ignore �łł̓e�X�g�R�[�h�̃R���p�C�����ʂ�Ȃ��Ă����Ȃ�
*/
#define IUTEST_TYPED_TEST_P_IGNORE(testcase_, testname_)	IIUT_TYPED_TEST_P_IGNORE_(testcase_, testname_)

#endif

#endif

#endif	// INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_
