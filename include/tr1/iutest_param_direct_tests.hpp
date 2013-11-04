//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_direct_tests.hpp
 * @brief		iris unit test initializer_list ���g�p�����p�����[�^�ݒ� �t�@�C��
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
#ifndef INCG_IRIS_iutest_param_direct_tests_HPP_8C9EC454_788D_4605_984B_0686C969E531_
#define INCG_IRIS_iutest_param_direct_tests_HPP_8C9EC454_788D_4605_984B_0686C969E531_

//======================================================================
// include
#include "../iutest_param_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

//======================================================================
// define

#undef IUTEST_INSTANTIATE_TEST_CASE_P
/**
 * @ingroup	TESTDEF
 * @def		IUTEST_INSTANTIATE_TEST_CASE_P
 * @brief	�p�����[�^�e�X�g�C���X�^���X���}�N��
 * @param	prefix_		= �C���X�^���X��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	generator_	= Range, Bool, Values, ValuesIn, Combine, Pairwise ...
*/
#define IUTEST_INSTANTIATE_TEST_CASE_P(prefix_, testcase_, ...)	\
													IIUT_INSTANTIATE_TEST_CASE_PV_(prefix_, testcase_, __VA_ARGS__)

/**
 * @private
 * @{
*/

/**
 * @brief	�p�����[�^�e�X�g�o�^(�ϒ��Ή�)
*/
#define IIUT_INSTANTIATE_TEST_CASE_PV_(prefix_, testcase_, ...)								\
	static ::iutest::detail::iuIParamGenerator<testcase_::ParamType>*						\
		s_##prefix_##_##testcase_##_EvalGenerator_(void) {									\
			return IUTEST_CAST_TO_PARAM_GENERATOR_(testcase_::ParamType, __VA_ARGS__); }	\
		int s_##prefix_##_##testcase_##_dummy =												\
			IIUT_GetTestCasePatternHolder(testcase_, IUTEST_CONCAT_PACKAGE_(testcase_))		\
				->AddTestCaseInstantiation(#prefix_, s_##prefix_##_##testcase_##_EvalGenerator_)

/**
 * @}
*/

//======================================================================
// function
namespace iutest {
namespace tr1
{

#if !defined(IUTEST_NO_VARIADIC_MACROS)

/**
 * @brief	initializer_list �Ή��p�L���X�g�I�u�W�F�N�g
*/
template<typename T>
detail::iuIParamGenerator<T>* iuCastToParamGenerator(detail::iuIParamGenerator<T>* g) { return g; }

#if IUTEST_HAS_INITIALIZER_LIST
template<typename T>
detail::iuIParamGenerator<T>* iuCastToParamGenerator(::std::initializer_list<T> l) { return new detail::iuValuesInParamsGenerator<T>(l); }
#endif

#define IUTEST_CAST_TO_PARAM_GENERATOR_(type, ...)	::iutest::tr1::iuCastToParamGenerator<type>(__VA_ARGS__)

#else

#define IUTEST_CAST_TO_PARAM_GENERATOR_(type, gen)	gen

#endif

}	// end of namespace tr1
}	// end of namespace iutest

#endif

#endif
