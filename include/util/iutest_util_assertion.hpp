//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_assertion.hpp
 * @brief		iris unit test assertion �g�� �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_
#define INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_

//======================================================================
// include
#include "../internal/iutest_type_traits.hpp"

namespace iuutil
{

//======================================================================
// define
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	== �e�X�g(collection)
 * @param	b1	= ���Ғl�̐擪
 * @param	e1	= ���Ғl�̏I�[
 * @param	b2	= �����Ώۂ̐擪
 * @param	e2	= �����Ώۂ̏I�[
*/
#ifndef IUTEST_ASSERT_EQ_COLLECTIONS
#  define	IUTEST_ASSERT_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	== �e�X�g(collection)
 * @param	b1	= ���Ғl�̐擪
 * @param	e1	= ���Ғl�̏I�[
 * @param	b2	= �����Ώۂ̐擪
 * @param	e2	= �����Ώۂ̏I�[
*/
#ifndef IUTEST_EXPECT_EQ_COLLECTIONS
#  define	IUTEST_EXPECT_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	== �e�X�g(collection)
 * @param	b1	= ���Ғl�̐擪
 * @param	e1	= ���Ғl�̏I�[
 * @param	b2	= �����Ώۂ̐擪
 * @param	e2	= �����Ώۂ̏I�[
*/
#ifndef IUTEST_INFORM_EQ_COLLECTIONS
#  define	IUTEST_INFORM_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME_
 * @brief	== �e�X�g(collection)
 * @param	b1	= ���Ғl�̐擪
 * @param	e1	= ���Ғl�̏I�[
 * @param	b2	= �����Ώۂ̐擪
 * @param	e2	= �����Ώۂ̏I�[
*/
#ifndef IUTEST_ASSUME_EQ_COLLECTIONS
#  define	IUTEST_ASSUME_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	== �e�X�g(range)
 * @param	expected	= ���Ғl
 * @param	actual		= �����Ώ�
*/
#ifndef IUTEST_ASSERT_EQ_RANGE
#  define	IUTEST_ASSERT_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	== �e�X�g(range)
 * @param	expected	= ���Ғl
 * @param	actual		= �����Ώ�
*/
#ifndef IUTEST_EXPECT_EQ_RANGE
#  define	IUTEST_EXPECT_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	== �e�X�g(range)
 * @param	expected	= ���Ғl
 * @param	actual		= �����Ώ�
*/
#ifndef IUTEST_INFORM_EQ_RANGE
#  define	IUTEST_INFORM_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME_
 * @brief	== �e�X�g(range)
 * @param	expected	= ���Ғl
 * @param	actual		= �����Ώ�
*/
#ifndef IUTEST_ASSUME_EQ_RANGE
#  define	IUTEST_ASSUME_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	�����񒷂̈�v �e�X�g
 * @param	len		= ���ҕ�����
 * @param	v2		= �����Ώ�
*/
#ifndef IUTEST_ASSERT_STRLNEQ
#  define	IUTEST_ASSERT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	�����񒷂̈�v �e�X�g
 * @param	len		= ���ҕ�����
 * @param	v2		= �����Ώ�
*/
#ifndef IUTEST_EXPECT_STRLNEQ
#  define	IUTEST_EXPECT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	�����񒷂̈�v �e�X�g
 * @param	len		= ���ҕ�����
 * @param	v2		= �����Ώ�
*/
#ifndef IUTEST_INFORM_STRLNEQ
#  define	IUTEST_INFORM_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	�����񒷂̈�v �e�X�g
 * @param	len		= ���ҕ�����
 * @param	v2		= �����Ώ�
*/
#ifndef IUTEST_ASSUME_STRLNEQ
#  define	IUTEST_ASSUME_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_ASSUME_FAILURE)
#endif

/**
* @ingroup	IUTEST_ASSERT_
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_ASSERT_STRIN
#  define	IUTEST_ASSERT_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
* @ingroup	IUTEST_EXPECT_
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_EXPECT_STRIN
#  define	IUTEST_EXPECT_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
* @ingroup	IUTEST_INFORM
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_INFORM_STRIN
#  define	IUTEST_INFORM_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_INFORM_FAILURE)
#endif
/**
* @ingroup	IUTEST_ASSUME
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_ASSUME_STRIN
#  define	IUTEST_ASSUME_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_ASSUME_FAILURE)
#endif


/**
* @ingroup	IUTEST_ASSERT_
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_ASSERT_STRNOTIN
#  define	IUTEST_ASSERT_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
* @ingroup	IUTEST_EXPECT_
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_EXPECT_STRNOTIN
#  define	IUTEST_EXPECT_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
* @ingroup	IUTEST_INFORM
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_INFORM_STRNOTIN
#  define	IUTEST_INFORM_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_INFORM_FAILURE)
#endif
/**
* @ingroup	IUTEST_ASSUME
* @brief	�����񕔕���v �e�X�g
* @param	substr	= ����������
* @param	actual	= �����Ώە�����
*/
#ifndef IUTEST_ASSUME_STRNOTIN
#  define	IUTEST_ASSUME_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_ASSUME_FAILURE)
#endif

#define ASSERT_EQ_COLLECTIONS	IUTEST_ASSERT_EQ_COLLECTIONS
#define ASSERT_EQ_RANGE			IUTEST_ASSERT_EQ_RANGE
#define ASSERT_STRLNEQ			IUTEST_ASSERT_STRLNEQ
#define ASSERT_STRIN			IUTEST_ASSERT_STRIN
#define ASSERT_STRNOTIN			IUTEST_ASSERT_STRNOTIN

#define EXPECT_EQ_COLLECTIONS	IUTEST_EXPECT_EQ_COLLECTIONS
#define EXPECT_EQ_RANGE			IUTEST_EXPECT_EQ_RANGE
#define EXPECT_STRLNEQ			IUTEST_EXPECT_STRLNEQ
#define EXPECT_STRIN			IUTEST_EXPECT_STRIN
#define EXPECT_STRNOTIN			IUTEST_EXPECT_STRNOTIN

#define INFORM_EQ_COLLECTIONS	IUTEST_INFORM_EQ_COLLECTIONS
#define INFORM_EQ_RANGE			IUTEST_INFORM_EQ_RANGE
#define INFORM_STRLNEQ			IUTEST_INFORM_STRLNEQ
#define INFORM_STRIN			IUTEST_INFORM_STRIN
#define INFORM_STRNOTIN			IUTEST_INFORM_STRNOTIN

#define ASSUME_EQ_COLLECTIONS	IUTEST_ASSUME_EQ_COLLECTIONS
#define ASSUME_EQ_RANGE			IUTEST_ASSUME_EQ_RANGE
#define ASSUME_STRLNEQ			IUTEST_ASSUME_STRLNEQ
#define ASSUME_STRIN			IUTEST_ASSUME_STRIN
#define ASSUME_STRNOTIN			IUTEST_ASSUME_STRNOTIN

/**
 * @private
 * @{
*/
#define IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, on_failure) IUTEST_PRED_FORMAT4_( ::iuutil::CmpHelperEqCollections, b1, e1, b2, e2, on_failure)
#define IUTEST_TEST_EQ_RANGE(expected, actual, on_failure) IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperEqRange, expected, actual, on_failure)

#define	IUTEST_TEST_STRLNEQ(len, v2, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRLNEQ, len, v2, on_failure )
#define IUTEST_TEST_STRIN(substr, actual, on_failure)		IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRIN, substr, actual, on_failure )
#define IUTEST_TEST_STRNOTIN(substr, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRNOTIN, substr, actual, on_failure )

/**
 * @}
*/

//======================================================================
// function
/**
 * @brief	Equal Collection Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqIterator(T1 b1, T1 e1, T2 b2, T2 e2)
{
	int elem=0;
	bool result = true;
	::iutest::Message ar;
	for(elem=0; b1 != e1 && b2 != e2; ++b1, ++b2, ++elem)
	{
		if(!::iutest::internal::EqHelper<false>::Compare("", "", *b1, *b2))
		{
			result = false;
			ar << "\nMismatch in a position " << elem << ": "
				<< ::iutest::internal::FormatForComparisonFailureMessage(*b1, *b2)
				<< " vs " << ::iutest::internal::FormatForComparisonFailureMessage(*b2, *b1);
		}
	}
	if(b1 != e1)
	{
		int elem1 = elem;
		for(; b1 != e1; ++b1, ++elem1)
			;
		result = false;
		ar << "\nMismatch element : " << elem1 << " vs " << elem;
	}
	if(b2 != e2)
	{
		int elem2 = elem;
		for(; b2 != e2; ++b2, ++elem2)
			;
		result = false;
		ar << "\nMismatch element : " << elem << " vs " << elem2;
	}
	if( !result )
	{
		return ::iutest::AssertionFailure() << ar;
	}
	return ::iutest::AssertionSuccess();
}

/**
 * @brief	Equal Collection Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqCollections(const char* expr1b, const char* expr1e, const char* expr2b, const char* expr2e
							   , T1 b1, T1 e1, T2 b2, T2 e2)
{
	if( ::iutest::AssertionResult ar = CmpHelperEqIterator(b1, e1, b2, e2) )
		;
	else
		return ::iutest::AssertionFailure() << "error: Expected: { " << expr1b << ", " << expr1e << " } == { "
			<< expr2b << ", " << expr2e << " }\n  Actual:" << ar.message();
	return ::iutest::AssertionSuccess();
}

namespace detail
{

template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 b1, T1 e1, T2 b2, T2 e2)
{
	if( ::iutest::AssertionResult ar = CmpHelperEqIterator(b1, e1, b2, e2) )
		;
	else
		return ::iutest::AssertionFailure() << "error: Expected: " << expected_expr << " == " << actual_expr
			<< " \n  Actual:" << ar.message();
	return ::iutest::AssertionSuccess();
}

}

/**
* @brief	Equal Range Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 expected, T2 actual)
{
//	return detail::CmpHelperEqRange(expected_expr, actual_expr, ::std::begin(expected), ::std::end(expected)
//		, ::std::begin(actual), ::std::end(actual));
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected.begin(), expected.end()
		, actual.begin(), actual.end());
}
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

/** @overload */
template<typename T1, size_t SIZE1, typename T2, size_t SIZE2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 (&expected)[SIZE1], T2 (&actual)[SIZE2])
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected, expected+SIZE1
		, actual, actual+SIZE2);
}
/** @overload */
template<typename T1, typename T2, size_t SIZE2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 expected, T2(&actual)[SIZE2])
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected.begin(), expected.end()
		, actual, actual+SIZE2);
}
/** @overload */
template<typename T1, size_t SIZE1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1(&expected)[SIZE1], T2 actual)
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected, expected+SIZE1
		, actual.begin(), actual.end());
}

#endif

/**
 * @brief	�����񒷃A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										 , size_t len1, const char* val2)
{
	const size_t len2 = strlen(val2);
	if( len2 == len1 )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == strlen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1 ;
}
/**
 * @brief	�����񒷃A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										 , size_t len1, const wchar_t* val2)
{
	const size_t len2 = wcslen(val2);
	if( len2 == len1 )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == wcslen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1 ;
}

/**
* @brief	�����񕔕���v�A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRIN(const char* substr_str, const char* actual_str
	, const char* substr, const char* actual)
{
	if( substr == NULL || actual == NULL )
	{
		if( substr == actual )
		{
			return ::iutest::AssertionSuccess();
		}
	}
	else if( strstr(actual, substr) != NULL )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") != NULL"
		<< "\n  Actual: " << "strstr(" << actual << ", " << substr << ") == NULL";
}

/**
* @brief	�����񕔕���v�A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRIN(const char* substr_str, const char* actual_str
	, const wchar_t* substr, const wchar_t* actual)
{
	if( substr == NULL || actual == NULL )
	{
		if( substr == actual )
		{
			return ::iutest::AssertionSuccess();
		}
	}
	else if( wcsstr(actual, substr) != NULL )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") != NULL"
		<< "\n  Actual: " << "strstr(" << actual << ", " << substr << ") == NULL";
}

/**
* @brief	�����񕔕���v�A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNOTIN(const char* substr_str, const char* actual_str
	, const char* substr, const char* actual)
{
	if( substr == NULL || actual == NULL )
	{
		if( substr != actual )
		{
			return ::iutest::AssertionSuccess();
		}
	}
	else if( strstr(actual, substr) == NULL )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") == NULL"
		<< "\n  Actual: " << "strstr(" << actual << ", " << substr << ") != NULL";
}

/**
* @brief	�����񕔕���v�A�T�[�V�����t�H�[�}�b�^�[
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNOTIN(const char* substr_str, const char* actual_str
	, const wchar_t* substr, const wchar_t* actual)
{
	if( substr == NULL || actual == NULL )
	{
		if( substr != actual )
		{
			return ::iutest::AssertionSuccess();
		}
	}
	else if( wcsstr(actual, substr) == NULL )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") == NULL"
		<< "\n  Actual: " << "strstr(" << actual << ", " << substr << ") != NULL";
}

/**
 * @private
 * @{
*/
#define IIUT_COMPARE_HELPER_DEC_(name)	struct name {										\
	template<typename T1, typename T2>														\
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const T1& val1, const T2& val2)	{	\
		return ::iutest::internal::CmpHelper##name(expr1, expr2, val1, val2);				\
	}																						\
	}
/**
 * @}
*/

/**
 * @brief	OR �e�X�g�p�I�u�W�F�N�g�S
*/
struct CmpHelper
{
	IIUT_COMPARE_HELPER_DEC_(EQ);	//!< OR �e�X�g�p EQ
	IIUT_COMPARE_HELPER_DEC_(NE);	//!< OR �e�X�g�p NE
	IIUT_COMPARE_HELPER_DEC_(LE);	//!< OR �e�X�g�p LE
	IIUT_COMPARE_HELPER_DEC_(LT);	//!< OR �e�X�g�p LT
	IIUT_COMPARE_HELPER_DEC_(GE);	//!< OR �e�X�g�p GE
	IIUT_COMPARE_HELPER_DEC_(GT);	//!< OR �e�X�g�p GT
};

#undef IIUT_COMPARE_HELPER_DEC_

/**
 * @brief	OR �e�X�g�p��r�w���p�[
*/
template<typename COMP>
struct CmpHelperOR
{
private:
	template<typename T, typename DMY>
	struct CompImpl
	{
		template<typename T1, typename T2>
		static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
			, T1 val1, T2 val2)
		{
			return T::Comp(expr1, expr2, val1, val2);
		}
	};
	template<typename DMY>
	struct CompImpl<CmpHelper::EQ, DMY>
	{
		template<typename T1, typename T2>
		static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
			, T1 val1, T2 val2)
		{
			// val1 == actual
			return CmpHelper::EQ::Comp(expr2, expr1, val2, val1);
		}
	};
public:

	/**
	 * @brief	�t�H�[�}�b�^�[
	*/
	template<typename T1, typename T2>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
		, T1 val1, T2 val2)
	{
		return CompImpl<COMP, void>::Comp(expr1, expr2, val1, val2);
	}
	/** @overload */
	template<typename T1, typename T2, typename T3>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3
		, T1 val1, T2 val2, T3 val3)
	{
		typename ::iutest_type_traits::add_rvalue_reference< ::iutest::AssertionResult >::type ar = Comp(expr1, expr2, val1, val2);
		if( ar ) return ar;
		return Comp(expr1, expr3, val1, val3) << "\n" << ar.message();
	}
	/** @overload */
	template<typename T1, typename T2, typename T3, typename T4>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3, const char* expr4
		, T1 val1, T2 val2, T3 val3, T4 val4)
	{
		typename ::iutest_type_traits::add_rvalue_reference< ::iutest::AssertionResult >::type ar =  Comp(expr1, expr2, expr3, val1, val2, val3);
		if( ar ) return ar;
		return Comp(expr1, expr4, val1, val4) << "\n" << ar.message();
	}
	/** @overload */
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3, const char* expr4, const char* expr5
		, T1 val1, T2 val2, T3 val3, T4 val4, T5 val5)
	{
		typename ::iutest_type_traits::add_rvalue_reference< ::iutest::AssertionResult >::type ar =  Comp(expr1, expr2, expr3, expr4, val1, val2, val3, val4);
		if( ar ) return ar;
		return Comp(expr1, expr5, val1, val5) << "\n" << ar.message();
	}
};

}	// end of namespace iuutil

#endif	// INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_
