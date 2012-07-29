//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest.hpp
 * @brief		iris unit test �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
 * 
 * @see			iutest_ver.h
 * @example		main.cpp
 * @example		sub.cpp
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_HPP_
#define INCG_IRIS_iutest_HPP_

//======================================================================
// include
#include "iutest_ver.h"
#include "iutest_param_tests.hpp"
#include "iutest_typed_tests.hpp"
#include "iutest_prod.hpp"
#include "iutest_static_assertion.hpp"
#include "listener/iutest_default_printer.hpp"
#include "listener/iutest_default_xml_generator.hpp"

namespace iutest
{
}	// end of namespace iutest

//======================================================================
// define
/**
 * @defgroup	TESTDEF		�e�X�g��`�}�N��
 * @brief		�e�X�g��`�}�N��
*/

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TEST(testcase_, testname_)
 * @brief	�e�X�g�֐���`�}�N��
*/
#define IUTEST_TEST(testcase_, testname_)			IUTEST_TEST_(testcase_, testname_, ::iutest::Test	\
														, ::iutest::internal::GetTestTypeId())

/**
 * @ingroup	TESTDEF
 * @def		IUTEST(testcase_, testname_)
 * @brief	�e�X�g�֐���`�}�N��
*/
#define IUTEST(testcase_, testname_)				IUTEST_TEST(testcase_, testname_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_F(testfixture_, testname_)
 * @brief	���[�U�[�w��e�X�g�֐���`�}�N��
*/
#define IUTEST_F(testfixture_, testname_)			IUTEST_TEST_(testfixture_, testname_, testfixture_	\
														, ::iutest::internal::GetTypeId< testfixture_ >())

#if IUTEST_HAS_PARAM_METHOD_TEST
/**
 * @ingroup	TESTDEF
 * @def		IUTEST_PMZ(testcase_, testname_, method_, ...)
 * @brief	�p�����^���C�Y�֐��R�[���e�X�g��`�}�N��
*/
#define IUTEST_PMZ(testcase_, testname_, method_, ...)	IIUT_TEST_PMZ_(testcase_, testname_, method_, ::iutest::Test	\
														, ::iutest::internal::GetTestTypeId(), __VA_ARGS__)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_PMZ_F(testfixture_, testname_, method_, ...)
 * @brief	�p�����^���C�Y�֐��R�[���e�X�g��`�}�N��
*/
#define IUTEST_PMZ_F(testfixture_, testname_, method_, ...)	IIUT_TEST_PMZ_(testfixture_, testname_, method_, testfixture_	\
														, ::iutest::internal::GetTypeId< testfixture_ >(), __VA_ARGS__)

#endif

/**
 * @ingroup	TESTDEF
 * @brief	iutest �̏���������
*/
#define IUTEST_INIT(argc_, argv_)					::iutest::InitIrisUnitTest(argc_, argv_)

/**
 * @ingroup	TESTDEF
 * @brief	���ׂẴe�X�g�����s����
*/
#define IUTEST_RUN_ALL_TESTS()						::iutest::UnitTestSource::GetInstance().Run()


/**
 * @defgroup	IUTEST_UTIL		�e�X�g�L�q�⏕
 * @brief		�e�X�g�L�q�⏕�}�N��
*/

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�X�R�[�v���̃e�X�g���b�Z�[�W�ւ̃��b�Z�[�W�ǉ�
*/
#define IUTEST_SCOPED_TRACE(msg)					IIUT_SCOPED_MESSAGE(msg)

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�����I�Ȑ���
*/
#ifndef IUTEST_SUCCEED
#  define IUTEST_SUCCEED()							IIUT_SUCCEED()
#endif

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�����I�Ȏ��s
*/
#ifndef IUTEST_FAIL
#  define IUTEST_FAIL()								IIUT_FAIL()
#endif

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�����I�Ȏ��s
*/
#ifndef IUTEST_ADD_FAILURE
#  define IUTEST_ADD_FAILURE()						IIUT_ADD_FAILURE()
#endif

/**
 * @ingroup		IUTEST_UTIL
 * @brief		�����I�Ȏ��s
*/
#ifndef IUTEST_ADD_FAILURE_AT
#  define IUTEST_ADD_FAILURE_AT(file, line)			IIUT_ADD_FAILURE_AT(file, line)
#endif

/**
 * @defgroup	IUTEST_ASSERT_	�A�T�[�V����(ASSERT)
 * @brief		�e�X�g�L�q�}�N��
 * @details		���s�����ꍇ�A���̎��_�Ńe�X�g���甲���܂��B
*/

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	== �e�X�g
*/
#ifndef IUTEST_ASSERT_EQ
#  define	IUTEST_ASSERT_EQ(expected, actual)		IUTEST_TEST_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	!= �e�X�g
*/
#ifndef IUTEST_ASSERT_NE
#  define	IUTEST_ASSERT_NE(v1, v2)				IUTEST_TEST_NE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	<= �e�X�g
*/
#ifndef IUTEST_ASSERT_LE
#  define	IUTEST_ASSERT_LE(v1, v2)				IUTEST_TEST_LE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	< �e�X�g
*/
#ifndef IUTEST_ASSERT_LT
#  define	IUTEST_ASSERT_LT(v1, v2)				IUTEST_TEST_LT(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	>= �e�X�g
*/
#ifndef IUTEST_ASSERT_GE
#  define	IUTEST_ASSERT_GE(v1, v2)				IUTEST_TEST_GE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	> �e�X�g
*/
#ifndef IUTEST_ASSERT_GT
#  define	IUTEST_ASSERT_GT(v1, v2)				IUTEST_TEST_GT(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	TRUE �e�X�g
*/
#ifndef IUTEST_ASSERT_TRUE
#  define	IUTEST_ASSERT_TRUE(v)					IUTEST_TEST_TRUE(v, #v, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	FALSE �e�X�g
*/
#ifndef IUTEST_ASSERT_FALSE
#  define	IUTEST_ASSERT_FALSE(v)					IUTEST_TEST_FALSE(v, #v, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	NULL �e�X�g
*/
#ifndef IUTEST_ASSERT_NULL
#  define	IUTEST_ASSERT_NULL(v)					IUTEST_TEST_NULL(v, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	NOT NULL �e�X�g
*/
#ifndef IUTEST_ASSERT_NOTNULL
#  define	IUTEST_ASSERT_NOTNULL(v)				IUTEST_TEST_NOTNULL(v, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	�A�h���X��v �e�X�g
*/
#ifndef IUTEST_ASSERT_SAME
#  define	IUTEST_ASSERT_SAME(v1, v2)				IUTEST_TEST_SAME(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	float �̔�r �e�X�g
*/
#ifndef IUTEST_ASSERT_FLOAT_EQ
#  define	IUTEST_ASSERT_FLOAT_EQ(expected, actual)	IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	double �̔�r �e�X�g
*/
#ifndef IUTEST_ASSERT_DOUBLE_EQ
#  define	IUTEST_ASSERT_DOUBLE_EQ(expected, actual)	IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	�Q�l�̍��͈̔� �e�X�g
*/
#ifndef IUTEST_ASSERT_NEAR
#  define	IUTEST_ASSERT_NEAR(v1, v2, abs_v)		IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	������̈�v �e�X�g
*/
#ifndef IUTEST_ASSERT_STREQ
#  define	IUTEST_ASSERT_STREQ(expected_str, actual_str)	IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	������̕s��v �e�X�g
*/
#ifndef IUTEST_ASSERT_STRNE
#  define	IUTEST_ASSERT_STRNE(v1, v2)				IUTEST_TEST_STRNE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	������̈�v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_ASSERT_STRCASEEQ
#  define	IUTEST_ASSERT_STRCASEEQ(expected_str, actual_str)	IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	������̕s��v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_ASSERT_STRCASENE
#  define	IUTEST_ASSERT_STRCASENE(v1, v2)			IUTEST_TEST_STRCASENE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	HRESULT �̐��� �e�X�g
*/
#ifndef IUTEST_ASSERT_HRESULT_SUCCEEDED
#  define IUTEST_ASSERT_HRESULT_SUCCEEDED(hr)		IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	HRESULT �̎��s �e�X�g
*/
#ifndef IUTEST_ASSERT_HRESULT_FAILED
#  define IUTEST_ASSERT_HRESULT_FAILED(hr)			IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_ASSERT_FAILURE)
#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	throw �e�X�g
*/
#ifndef IUTEST_ASSERT_THROW
#  define IUTEST_ASSERT_THROW(statement, expected_exception)	\
													IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	any throw �e�X�g
*/
#ifndef IUTEST_ASSERT_ANY_THROW
#  define IUTEST_ASSERT_ANY_THROW(statement)		IUTEST_TEST_ANY_THROW_(statement, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	no throw �e�X�g
*/
#ifndef IUTEST_ASSERT_NO_THROW
#  define IUTEST_ASSERT_NO_THROW(statement)			IUTEST_TEST_NO_THROW_(statement, IUTEST_ASSERT_FAILURE)
#endif

#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	no new failure �e�X�g
*/
#ifndef IUTEST_ASSERT_NO_FATAL_FAILURE
#  define IUTEST_ASSERT_NO_FATAL_FAILURE(statement)	IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	�����I�Ȏ��s
*/
#ifndef IUTEST_ASSERT_FAIL
#  define IUTEST_ASSERT_FAIL()						IIUT_FAIL()
#endif



/**
 * @defgroup	IUTEST_EXPECT_		�A�T�[�V����(EXPECT)
 * @brief		�e�X�g�L�q�}�N��
 * @details		���s�����ꍇ�ł��A�e�X�g�𑱍s���܂��B
*/

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	== �e�X�g
*/
#ifndef IUTEST_EXPECT_EQ
#  define	IUTEST_EXPECT_EQ(expected, actual)		IUTEST_TEST_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	!= �e�X�g
*/
#ifndef IUTEST_EXPECT_NE
#  define	IUTEST_EXPECT_NE(v1, v2)				IUTEST_TEST_NE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	<= �e�X�g
*/
#ifndef IUTEST_EXPECT_LE
#  define	IUTEST_EXPECT_LE(v1, v2)				IUTEST_TEST_LE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	< �e�X�g
*/
#ifndef IUTEST_EXPECT_LT
#  define	IUTEST_EXPECT_LT(v1, v2)				IUTEST_TEST_LT(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	>= �e�X�g
*/
#ifndef IUTEST_EXPECT_GE
#  define	IUTEST_EXPECT_GE(v1, v2)				IUTEST_TEST_GE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	> �e�X�g
*/
#ifndef IUTEST_EXPECT_GT
#  define	IUTEST_EXPECT_GT(v1, v2)				IUTEST_TEST_GT(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	TRUE �e�X�g
*/
#ifndef IUTEST_EXPECT_TRUE
#  define	IUTEST_EXPECT_TRUE(v)					IUTEST_TEST_TRUE(v, #v, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	FALSE �e�X�g
*/
#ifndef IUTEST_EXPECT_FALSE
#  define	IUTEST_EXPECT_FALSE(v)					IUTEST_TEST_FALSE(v, #v, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	NULL �e�X�g
*/
#ifndef IUTEST_EXPECT_NULL
#  define	IUTEST_EXPECT_NULL(v)					IUTEST_TEST_NULL(v, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	NOT NULL �e�X�g
*/
#ifndef IUTEST_EXPECT_NOTNULL
#  define	IUTEST_EXPECT_NOTNULL(v)				IUTEST_TEST_NOTNULL(v, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	�A�h���X��v �e�X�g
*/
#ifndef IUTEST_EXPECT_SAME
#  define	IUTEST_EXPECT_SAME(v1, v2)				IUTEST_TEST_SAME(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	float �̔�r �e�X�g
*/
#ifndef IUTEST_EXPECT_FLOAT_EQ
#  define	IUTEST_EXPECT_FLOAT_EQ(expected, actual)	IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	double �̔�r �e�X�g
*/
#ifndef IUTEST_EXPECT_DOUBLE_EQ
#  define	IUTEST_EXPECT_DOUBLE_EQ(expected, actual)	IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	�Q�l�̍��͈̔� �e�X�g
*/
#ifndef IUTEST_EXPECT_NEAR
#  define	IUTEST_EXPECT_NEAR(v1, v2, abs_v)		IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	������̈�v �e�X�g
*/
#ifndef IUTEST_EXPECT_STREQ
#  define	IUTEST_EXPECT_STREQ(expected_str, actual_str)	IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	������̕s��v �e�X�g
*/
#ifndef IUTEST_EXPECT_STRNE
#  define	IUTEST_EXPECT_STRNE(v1, v2)				IUTEST_TEST_STRNE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	������̈�v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_EXPECT_STRCASEEQ
#  define	IUTEST_EXPECT_STRCASEEQ(expected_str, actual_str)	IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	������̕s��v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_EXPECT_STRCASENE
#  define	IUTEST_EXPECT_STRCASENE(v1, v2)			IUTEST_TEST_STRCASENE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	HRESULT �̐��� �e�X�g
*/
#ifndef IUTEST_EXPECT_HRESULT_SUCCEEDED
#  define IUTEST_EXPECT_HRESULT_SUCCEEDED(hr)		IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	HRESULT �̎��s �e�X�g
*/
#ifndef IUTEST_EXPECT_HRESULT_FAILED
#  define IUTEST_EXPECT_HRESULT_FAILED(hr)			IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_EXPECT_FAILURE)
#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	throw �e�X�g
*/
#ifndef IUTEST_EXPECT_THROW
#  define IUTEST_EXPECT_THROW(statement, expected_exception)	\
													IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	any throw �e�X�g
*/
#ifndef IUTEST_EXPECT_ANY_THROW
#  define IUTEST_EXPECT_ANY_THROW(statement)		IUTEST_TEST_ANY_THROW_(statement, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	no throw �e�X�g
*/
#ifndef IUTEST_EXPECT_NO_THROW
#  define IUTEST_EXPECT_NO_THROW(statement)			IUTEST_TEST_NO_THROW_(statement, IUTEST_EXPECT_FAILURE)
#endif

#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	no new failure �e�X�g
*/
#ifndef IUTEST_EXPECT_NO_FATAL_FAILURE
#  define IUTEST_EXPECT_NO_FATAL_FAILURE(statement)	IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	�����I�Ȏ��s
*/
#ifndef IUTEST_EXPECT_FAIL
#  define IUTEST_EXPECT_FAIL()						IIUT_ADD_FAILURE()
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	�����I�Ȏ��s
*/
#ifndef IUTEST_EXPECT_FAIL_AT
#  define IUTEST_EXPECT_FAIL_AT(file, line)			IIUT_ADD_FAILURE_AT(file, line)
#endif



/**
 * @defgroup	IUTEST_INFORM_		�A�T�[�V����(INFORM)
 * @brief		�e�X�g�L�q�}�N��
 * @details		���s�����ꍇ�ł��A�e�X�g���s�Ƃ��ċL�^���܂���B�܂��A�e�X�g�͑��s���܂��B
*/

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	== �e�X�g
*/
#ifndef IUTEST_INFORM_EQ
#  define	IUTEST_INFORM_EQ(expected, actual)		IUTEST_TEST_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	!= �e�X�g
*/
#ifndef IUTEST_INFORM_NE
#  define	IUTEST_INFORM_NE(v1, v2)				IUTEST_TEST_NE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	<= �e�X�g
*/
#ifndef IUTEST_INFORM_LE
#  define	IUTEST_INFORM_LE(v1, v2)				IUTEST_TEST_LE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	< �e�X�g
*/
#ifndef IUTEST_INFORM_LT
#  define	IUTEST_INFORM_LT(v1, v2)				IUTEST_TEST_LT(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	>= �e�X�g
*/
#ifndef IUTEST_INFORM_GE
#  define	IUTEST_INFORM_GE(v1, v2)				IUTEST_TEST_GE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	> �e�X�g
*/
#ifndef IUTEST_INFORM_GT
#  define	IUTEST_INFORM_GT(v1, v2)				IUTEST_TEST_GT(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	TRUE �e�X�g
*/
#ifndef IUTEST_INFORM_TRUE
#  define	IUTEST_INFORM_TRUE(v)					IUTEST_TEST_TRUE(v, #v, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	FALSE �e�X�g
*/
#ifndef IUTEST_INFORM_FALSE
#  define	IUTEST_INFORM_FALSE(v)					IUTEST_TEST_FALSE(v, #v, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	NULL �e�X�g
*/
#ifndef IUTEST_INFORM_NULL
#  define	IUTEST_INFORM_NULL(v)					IUTEST_TEST_NULL(v, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	NOT NULL �e�X�g
*/
#ifndef IUTEST_INFORM_NOTNULL
#  define	IUTEST_INFORM_NOTNULL(v)				IUTEST_TEST_NOTNULL(v, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	�A�h���X��v �e�X�g
*/
#ifndef IUTEST_INFORM_SAME
#  define	IUTEST_INFORM_SAME(v1, v2)				IUTEST_TEST_SAME(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	float �̔�r �e�X�g
*/
#ifndef IUTEST_INFORM_FLOAT_EQ
#  define	IUTEST_INFORM_FLOAT_EQ(expected, actual)	IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	double �̔�r �e�X�g
*/
#ifndef IUTEST_INFORM_DOUBLE_EQ
#  define	IUTEST_INFORM_DOUBLE_EQ(expected, actual)	IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	�Q�l�̍��͈̔� �e�X�g
*/
#ifndef IUTEST_INFORM_NEAR
#  define	IUTEST_INFORM_NEAR(v1, v2, abs_v)		IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	������̈�v �e�X�g
*/
#ifndef IUTEST_INFORM_STREQ
#  define	IUTEST_INFORM_STREQ(expected_str, actual_str)	IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	������̕s��v �e�X�g
*/
#ifndef IUTEST_INFORM_STRNE
#  define	IUTEST_INFORM_STRNE(v1, v2)				IUTEST_TEST_STRNE(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	������̈�v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_INFORM_STRCASEEQ
#  define	IUTEST_INFORM_STRCASEEQ(expected_str, actual_str)	IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	������̕s��v�i�啶����������ʂȂ��j �e�X�g
*/
#ifndef IUTEST_INFORM_STRCASENE
#  define	IUTEST_INFORM_STRCASENE(v1, v2)			IUTEST_TEST_STRCASENE(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	HRESULT �̐��� �e�X�g
*/
#ifndef IUTEST_INFORM_HRESULT_SUCCEEDED
#  define IUTEST_INFORM_HRESULT_SUCCEEDED(hr)		IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	HRESULT �̎��s �e�X�g
*/
#ifndef IUTEST_INFORM_HRESULT_FAILED
#  define IUTEST_INFORM_HRESULT_FAILED(hr)			IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_INFORM_FAILURE)
#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	throw �e�X�g
*/
#ifndef IUTEST_INFORM_THROW
#  define IUTEST_INFORM_THROW(statement, expected_exception)	\
													IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	any throw �e�X�g
*/
#ifndef IUTEST_INFORM_ANY_THROW
#  define IUTEST_INFORM_ANY_THROW(statement)		IUTEST_TEST_ANY_THROW_(statement, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	no throw �e�X�g
*/
#ifndef IUTEST_INFORM_NO_THROW
#  define IUTEST_INFORM_NO_THROW(statement)			IUTEST_TEST_NO_THROW_(statement, IUTEST_INFORM_FAILURE)
#endif

#endif

/**
 * @ingroup	IUTEST_INFORM_
 * @brief	no new failure �e�X�g
*/
#ifndef IUTEST_INFORM_NO_FATAL_FAILURE
#  define IUTEST_INFORM_NO_FATAL_FAILURE(statement)	IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_INFORM_FAILURE)
#endif


/**
 * @brief iutest root namespace
*/
namespace iutest
{

//======================================================================
// class
/**
 * @brief	�P�̃e�X�g�N�_
*/
class UnitTestSource
{
public:
	/** @private */
	static UnitTestSource&	GetInstance(void)	{ static UnitTestSource inst; return inst; }

private:
	UnitTestSource(void)
	{
#if defined(_IUTEST_DEBUG)
		detail::iuDebugInitialize();
#endif
		TestEnv::event_listeners().set_default_result_printer(new DefalutResultPrintListener());
	}
	~UnitTestSource(void)
	{
		{
			TestEventListener* listener = TestEnv::event_listeners().default_result_printer();
			delete listener;
		}
		{
			TestEventListener* listener = TestEnv::event_listeners().default_xml_generator();
			delete listener;
		}
	}

public:
	/**
	 * @brief	������
	*/
	void	Initialize(void)
	{
		if( TestFlag::IsEnableFlag(TestFlag::OUTPUT_XML_REPORT) )
		{
			DefaultXmlGeneratorListener* listener = new DefaultXmlGeneratorListener();
			listener->SetFilePath(TestEnv::get_report_filepath());
			TestEnv::event_listeners().set_default_xml_generator(listener);
		}

		UnitTest::instance().Initialize();
	}

	/**
	 * @brief	�e�X�g�̎��s
	*/
	int	Run(void)
	{
		return UnitTest::instance().Run();
	}
};

//======================================================================
// function
/**
 * @brief	������
 * @details	�R�}���h���C���I�v�V�����̉�͂����܂��B
 *			�g�p���������͍폜���� pargc, argv �����������܂�
*/
inline void	IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, char** argv)		{ TestEnv::ParseCommandLine(pargc, argv); UnitTestSource::GetInstance().Initialize(); }
inline void	IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, wchar_t** argv)	{ TestEnv::ParseCommandLine(pargc, argv); UnitTestSource::GetInstance().Initialize(); }		//!< @overload
inline void	IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const char** argv)	{ TestEnv::ParseCommandLine(pargc, argv); UnitTestSource::GetInstance().Initialize(); }	//!< @overload
inline void	IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const wchar_t** argv)	{ TestEnv::ParseCommandLine(pargc, argv); UnitTestSource::GetInstance().Initialize(); }	//!< @overload

/** @overload */
template<typename CharType>
inline void	IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(::std::vector< ::std::basic_string<CharType> >& argv)
{
	TestEnv::ParseCommandLine(argv); UnitTestSource::GetInstance().Initialize();
}

/**
 * @brief	�O���[�o�����Z�b�g�N���X�̒ǉ�
 * @param [in]	env	= ���Z�b�g�N���X�A�h���X
 * @return	�o�^���ꂽ�N���X�A�h���X
 * @note	�������Ǘ��͂��Ȃ��Bnew ���� Environment �̓��[�U�[���������
*/
inline Environment IUTEST_ATTRIBUTE_UNUSED_ * AddGlobalTestEnvironment(Environment* env)
{
	return TestEnv::AddGlobalTestEnvironment(env);
}

}

#ifdef IUTEST_USE_GTEST
#  include "gtest/iutest_switch.hpp"
#endif

#include "iutest_util.hpp"

#endif
