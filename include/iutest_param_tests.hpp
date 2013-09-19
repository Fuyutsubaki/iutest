//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_tests.hpp
 * @brief		iris unit test parameter ��` �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_param_tests_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_
#define INCG_IRIS_iutest_param_tests_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_

//======================================================================
// include
#include "iutest_core.hpp"
#include "iutest_any.hpp"

#if IUTEST_HAS_PARAM_TEST
#include "internal/iutest_pool.hpp"

//======================================================================
// define
/**
 * @ingroup	TESTDEF
 * @def		IUTEST_INSTANTIATE_TEST_CASE_P
 * @brief	�p�����[�^�e�X�g�C���X�^���X���}�N��
 * @param	prefix_		= �C���X�^���X��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	generator_	= Range, Bool, Values, ValuesIn, Combine, Pairwise ...
*/
#define IUTEST_INSTANTIATE_TEST_CASE_P(prefix_, testcase_, generator_)	\
													IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_P(testcase_, testname_)
 * @brief	�p�����[�^���[�U�[�w��e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
 * @note	
 *	class TestCaseName : public ::iutest::TestWithParam<int> {};\n
 *  IUTEST_P(TestCaseName, TestName) {}\n
 *  IUTEST_INSTANTIATE_TEST_CASE_P(InstantiateName, TestCaseName, ParamGenerator);\n
*/
#define IUTEST_P(testcase_, testname_)				IIUT_TEST_P_(testcase_, testname_)

/**
 * @private
 * @{
*/

#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#  define IIUT_GetTestCasePatternHolder(T, testcase_)	\
	::iutest::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder<T>(testcase_)
#else
#  define IIUT_GetTestCasePatternHolder(T, testcase_)	\
	::iutest::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder(testcase_, &::iutest::detail::type<T>())
#endif

/**
 * @brief	�p�����[�^�e�X�g�o�^
*/
#define IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)						\
	static ::iutest::detail::iuIParamGenerator< IUTEST_TO_VARNAME_(testcase_)::ParamType >*	\
		IUTEST_TEST_P_EVALGENERATOR_NAME_(prefix_, testcase_)(void) { return generator_; }	\
		int IUTEST_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testcase_)(void) {			\
			::iutest::ParamTestCaseInfo< IUTEST_TO_VARNAME_(testcase_) >* p =				\
				IIUT_GetTestCasePatternHolder( IUTEST_TO_VARNAME_(testcase_)				\
					, IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)) );					\
			return p->AddTestCaseInstantiation(#prefix_, IUTEST_TEST_P_EVALGENERATOR_NAME_(prefix_, testcase_));	\
		} IUTEST_TEST_P_INSTANTIATIONREGISTER_(prefix_, testcase_)
				

/**
 * @brief	�p�����[�^�e�X�g�N���X��`
*/
#define IIUT_TEST_P_(testcase_, testname_)															\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public IUTEST_TO_VARNAME_(testcase_) {	\
		public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}								\
		protected: virtual void Body(void);															\
		private: static int	AddRegister(void) {														\
			static ::iutest::detail::ParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_			\
				, testname_) > testinfo(IUTEST_TO_NAME_STR_(testname_));							\
			IIUT_GetTestCasePatternHolder(IUTEST_TO_VARNAME_(testcase_), IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)))	\
				->AddTestPattern(&testinfo); return 0;												\
		}																							\
		static int dummy_;																			\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));			\
	};																								\
	int IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::dummy_ IUTEST_ATTRIBUTE_UNUSED_				\
		= IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::AddRegister();								\
	void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

#define IIUT_TEST_P_IGNORE_(testcase_, testname_)													\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public IUTEST_TO_VARNAME_(testcase_) {	\
		public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}								\
		protected: virtual void Body(void) { IUTEST_SKIP() << "ignored test..."; }					\
		template<typename T>void Body(void);														\
		private: static int	AddRegister(void) {														\
			static ::iutest::detail::ParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_			\
				, testname_) > testinfo(IUTEST_TO_NAME_STR_(testname_));							\
			IIUT_GetTestCasePatternHolder(IUTEST_TO_VARNAME_(testcase_), IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)))	\
				->AddTestPattern(&testinfo); return 0;												\
		}																							\
		static int dummy_;																			\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));			\
	};																								\
	int IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::dummy_ IUTEST_ATTRIBUTE_UNUSED_				\
		= IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::AddRegister();								\
	template<typename T>void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

#define IUTEST_TEST_P_EVALGENERATOR_NAME_(prefix_, testcase_)	IIUT_TEST_P_EVALGENERATOR_NAME_I(prefix_, IUTEST_TO_VARNAME_(testcase_))
#define IIUT_TEST_P_EVALGENERATOR_NAME_I(prefix_, testcase_)	IIUT_TEST_P_EVALGENERATOR_NAME_I_(prefix_, testcase_)
#define IIUT_TEST_P_EVALGENERATOR_NAME_I_(prefix_, testcase_)	s_##prefix_##_##testcase_##_EvalGenerator_

#define IUTEST_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testcase_)	IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I(prefix_, IUTEST_TO_VARNAME_(testcase_))
#define IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I(prefix_, testcase_)	IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I_(prefix_, testcase_)
#define IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I_(prefix_, testcase_)	prefix_##_##testcase_##_TestCaseInstantiationRegister

#define IUTEST_TEST_P_INSTANTIATIONREGISTER_(prefix_, testcase_)			IIUT_TEST_P_INSTANTIATIONREGISTER_I(prefix_, IUTEST_TO_VARNAME_(testcase_), IUTEST_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testcase_))
#define IIUT_TEST_P_INSTANTIATIONREGISTER_I(prefix_, testcase_, register_)	IIUT_TEST_P_INSTANTIATIONREGISTER_I_(prefix_, testcase_, register_)
#define IIUT_TEST_P_INSTANTIATIONREGISTER_I_(prefix_, testcase_, register_)	int s_##prefix_##_##testcase_##_dummy = register_()

/**
 * @}
*/

//======================================================================
// class
namespace iutest {
namespace detail
{

/**
 * @brief	�p�����[�^�P�̃e�X�g TestInfo ���C���X�^���X
*/
template<typename T>
class ParamTestInstance : public IParamTestInfoData<typename T::ParamType>
{
	typedef T								Tester;
	typedef typename Tester::ParamType		ParamType;
	typedef detail::iuParamTestFactory<T>	Factory;
	typedef IParamTestInfoData<ParamType>	_Mybase;

	// �e�e�X�g�̃C���X�^���X
	class EachTest
	{
	public:
		EachTest(TestCase* testcase, const char* name, ParamType param)
			: m_mediator(testcase)
			, m_factory(param)
			, m_info(&m_mediator, name, &m_factory)
		{
			UnitTest::instance().AddTestInfo(testcase, &m_info);
			m_info.set_value_param(PrintToString(param).c_str());
		}
	private:
		TestCaseMediator	m_mediator;
		Factory				m_factory;
		TestInfo			m_info;
	};
public:
	ParamTestInstance(const char* testcase_name) : _Mybase(testcase_name) {}

private:
	// �e�X�g�P�[�X�̍쐬
	virtual TestCase*	MakeTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown) const IUTEST_CXX_OVERRIDE
	{
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
		return UnitTest::instance().AddTestCase<TestCase>(testcase_name, id, setup, teardown);
#else
		return UnitTest::instance().AddTestCase(testcase_name, id, setup, teardown, &detail::type<TestCase>());
#endif
	}

	// �e�X�g�̍쐬�o�^
	virtual	void	RegisterTest(TestCase* testcase, ParamType param, int index) const IUTEST_CXX_OVERRIDE
	{
		EachTest* test = new EachTest(testcase, detail::MakeIndexTestName(this->m_name.c_str(), index).c_str(), param);
		// new �I�u�W�F�N�g���Ǘ����Ă��炤
		detail::iuPool<EachTest>::GetInstance().push(test);
	}
};

}	// end of namespace detail

/**
 * @brief	any �p�����[�^�e�X�g�t�B�N�X�`��
*/
class TestWithAny : virtual public Test, public WithParamInterface<any>
{
public:
	/**
	 * @brief	�p�����[�^�̎擾
	*/
	static const ParamType&	GetParam(void) { return WithParamInterface<any>::GetParam(); }

	/**
	 * @brief	�p�����[�^�̎擾
	*/
	template<typename T>
	static T GetParam(void) { return unsafe_any_cast<T>(WithParamInterface<any>::GetParam()); }
};

/**
 * @brief	�͈̓p�����[�^
*/
template<typename T>
detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ Range(T begin, T end, T step=1)
{
	return new detail::iuRangeParamsGenerator<T>(begin, end, step);
}

/**
 * @brief	�^�U�l�p�����[�^
*/
inline detail::iuParamGenerator<bool> IUTEST_ATTRIBUTE_UNUSED_ Bool(void)
{
	return new detail::iuBoolParamsGenerator<bool>();
}

#if IUTEST_HAS_VALUESGEN

/**
 * @brief	�l�z��p�����[�^
*/
template<typename Generator>
inline detail::iuValuesParamsGeneratorHolder<Generator> IUTEST_ATTRIBUTE_UNUSED_ ValuesGen(size_t num, const Generator& gen)
{
	return detail::iuValuesParamsGeneratorHolder<Generator>(num, gen);
}

/**
 * @brief	�����W�F�l���[�^
*/
template<typename T, typename F>
inline detail::iuRandomFilterParamGenerator<T, F> IUTEST_ATTRIBUTE_UNUSED_ RandomGenerator(const F& fn, unsigned int seed=0)
{
	if( seed == 0 )
	{
		seed = detail::GetIndefiniteValue();
	}
	return detail::iuRandomFilterParamGenerator<T, F>(fn, seed);
}

#endif

#if IUTEST_HAS_RANDOMVALUES
/**
 * @brief	�����l�p�����[�^
*/
inline detail::iuRandomParamsHolder IUTEST_ATTRIBUTE_UNUSED_ RandomValues(size_t num, unsigned int seed=0)
{
	return detail::iuRandomParamsHolder(num, seed);
}
#endif

/**
 * @brief	�l�z��p�����[�^
*/
template<typename Container>
inline detail::iuParamGenerator< typename Container::value_type > IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(Container containor)
{
	return new detail::iuValuesInParamsGenerator< typename Container::value_type >(containor);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/** @overload */
template<typename T, size_t SIZE>
inline detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(const T (&v)[SIZE])
{
	return new detail::iuValuesInParamsGenerator<T>(v, v+SIZE);
}
/** @overload */
template<typename Ite>
inline detail::iuParamGenerator< typename detail::IteratorTraits<Ite>::type > IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(Ite begin, Ite end)
{
	return new detail::iuValuesInParamsGenerator< typename detail::IteratorTraits<Ite>::type >(begin, end);
}
#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
inline detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(::std::initializer_list<T> l)
{
	return new detail::iuValuesInParamsGenerator<T>(l);
}
#endif

#endif

#if IUTEST_HAS_VARIADIC_VALUES
/**
 * @brief	�l�z��p�����[�^
*/
template<typename ...Args>
inline detail::iuValueArray<Args...> IUTEST_ATTRIBUTE_UNUSED_ Values(Args... args)
{
	return detail::iuValueArray<Args...>(args...);
}

#else

#define IIUT_DECL_VALUES_(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >					\
	inline detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >									\
	IUTEST_ATTRIBUTE_UNUSED_ Values( IUTEST_PP_ENUM_BINARY_PARAMS(n, T, t) )	{					\
	return detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >( IUTEST_PP_ENUM_PARAMS(n, t) );	\
	}

/**
 * @brief	�l�z��p�����[�^
 * @note	50�����܂Ŏg�p�\
*/
IIUT_DECL_VALUES_(1)
IIUT_DECL_VALUES_(2)
IIUT_DECL_VALUES_(3)
IIUT_DECL_VALUES_(4)
IIUT_DECL_VALUES_(5)
IIUT_DECL_VALUES_(6)
IIUT_DECL_VALUES_(7)
IIUT_DECL_VALUES_(8)
IIUT_DECL_VALUES_(9)
IIUT_DECL_VALUES_(10)
IIUT_DECL_VALUES_(11)
IIUT_DECL_VALUES_(12)
IIUT_DECL_VALUES_(13)
IIUT_DECL_VALUES_(14)
IIUT_DECL_VALUES_(15)
IIUT_DECL_VALUES_(16)
IIUT_DECL_VALUES_(17)
IIUT_DECL_VALUES_(18)
IIUT_DECL_VALUES_(19)
IIUT_DECL_VALUES_(20)
IIUT_DECL_VALUES_(21)
IIUT_DECL_VALUES_(22)
IIUT_DECL_VALUES_(23)
IIUT_DECL_VALUES_(24)
IIUT_DECL_VALUES_(25)
IIUT_DECL_VALUES_(26)
IIUT_DECL_VALUES_(27)
IIUT_DECL_VALUES_(28)
IIUT_DECL_VALUES_(29)
IIUT_DECL_VALUES_(30)
IIUT_DECL_VALUES_(31)
IIUT_DECL_VALUES_(32)
IIUT_DECL_VALUES_(33)
IIUT_DECL_VALUES_(34)
IIUT_DECL_VALUES_(35)
IIUT_DECL_VALUES_(36)
IIUT_DECL_VALUES_(37)
IIUT_DECL_VALUES_(38)
IIUT_DECL_VALUES_(39)
IIUT_DECL_VALUES_(40)
IIUT_DECL_VALUES_(41)
IIUT_DECL_VALUES_(42)
IIUT_DECL_VALUES_(43)
IIUT_DECL_VALUES_(44)
IIUT_DECL_VALUES_(45)
IIUT_DECL_VALUES_(46)
IIUT_DECL_VALUES_(47)
IIUT_DECL_VALUES_(48)
IIUT_DECL_VALUES_(49)
IIUT_DECL_VALUES_(50)

#undef IIUT_DECL_VALUES_

#endif

#if IUTEST_HAS_CONCAT
/**
 * @brief	�p�����[�^�̌���
*/
template<typename G1, typename G2>
detail::iuConcatParamHolder<G1, G2> Concat(const G1& g1, const G2& g2)
{
	return detail::iuConcatParamHolder<G1, G2>(g1, g2);
}
#endif

#if IUTEST_HAS_COMBINE

#if IUTEST_HAS_VARIADIC_COMBINE
/**
 * @brief	���������p�����[�^��
*/
template<typename ...Generator>
detail::iuCartesianProductHolder<Generator...> Combine(const Generator&... generators)
{
	return detail::iuCartesianProductHolder<Generator...>(generators...);
}

#else

#define IIUT_DECL_COMBINE_(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >				\
	inline IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
	Combine(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {										\
		return IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)								\
				< IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));					\
	}

/**
 * @brief	���������p�����[�^��
 * @note	9�����܂Ŏg�p�\
*/
IIUT_DECL_COMBINE_(2)
IIUT_DECL_COMBINE_(3)
IIUT_DECL_COMBINE_(4)
IIUT_DECL_COMBINE_(5)
IIUT_DECL_COMBINE_(6)
IIUT_DECL_COMBINE_(7)
IIUT_DECL_COMBINE_(8)
IIUT_DECL_COMBINE_(9)

#undef IIUT_DECL_COMBINE_

#endif

#endif

#if IUTEST_HAS_PAIRWISE

#if IUTEST_HAS_VARIADIC_PAIRWISE

/**
 * @brief	���������p�����[�^��(�I�[���y�A�@)
*/
template<typename ...Generator>
detail::iuPairwiseHolder<Generator...> Pairwise(const Generator&... generators)
{
	return detail::iuPairwiseHolder<Generator...>(generators...);
}

#else

#define IIUT_DECL_PAIRWISE_(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >			\
	inline IUTEST_PP_CAT(detail::iuPairwiseHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >		\
	Pairwise(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {								\
		return IUTEST_PP_CAT(detail::iuPairwiseHolder, n)									\
				< IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));				\
	}

/**
 * @brief	���������p�����[�^��(�I�[���y�A�@)
 * @note	9�����܂Ŏg�p�\
*/
IIUT_DECL_PAIRWISE_(2)
IIUT_DECL_PAIRWISE_(3)
IIUT_DECL_PAIRWISE_(4)
IIUT_DECL_PAIRWISE_(5)
IIUT_DECL_PAIRWISE_(6)
IIUT_DECL_PAIRWISE_(7)
IIUT_DECL_PAIRWISE_(8)
IIUT_DECL_PAIRWISE_(9)

#undef IIUT_DECL_PAIRWISE__

#endif

#endif

}	// end of namespace iutest

#endif	// IUTEST_HAS_PARAM_TEST

#endif
