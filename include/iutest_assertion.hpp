//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assertion.hpp
 * @brief		iris unit test assertion ��` �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ASSERTION_HPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_
#define INCG_IRIS_IUTEST_ASSERTION_HPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_

//======================================================================
// include
#include "iutest_result.hpp"
#include "iutest_printers.hpp"
#include "internal/iutest_list.hpp"

namespace iutest_report_result
{
	//! TestPartResultReporter ���Ȃ��ꍇ�̏����֐�
	void ReportTestPartResult(const ::iutest::TestPartResult& test_part_result);
}

namespace iutest
{

//! Message �N���X
typedef detail::iuStreamMessage	Message;

//======================================================================
// class
/**
 * @brief	�e�X�g����
*/
class AssertionResult
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in] result = �e�X�g���ʐ^�U�l
	*/
	AssertionResult(bool result) : m_result(result) {}
	//! �R�s�[�R���X�g���N�^
	AssertionResult(const AssertionResult& rhs) : m_message(rhs.m_message), m_result(rhs.m_result) {}

	/**
	 * @brief	����
	*/
	bool	failed(void) const IUTEST_CXX_NOEXCEPT_SPEC { return !m_result; }

	/**
	 * @brief	���b�Z�[�W�̎擾
	*/
	const char* message(void)	const	{ return m_message.c_str(); }

	/**
	 * @brief	���b�Z�[�W�̎擾
	 * @deprecated please use message() instead.
	*/
	const char* failure_message(void) const { return message(); }

	/** @private */
	IUTEST_CXX_EXPLICIT_CONVERSION operator bool (void)	const	{ return m_result; }

public:
	/**
	 * @brief	���b�Z�[�W�ǉ�
	*/
	template<typename T>
	AssertionResult& operator << (T value)
	{
		Message msg;
		msg << value;
		m_message += msg.GetString();
		return *this;
	}

public:
	/**
	 * @brief	�������ʂ̍쐬
	*/
	static AssertionResult	Success(void)	{ return AssertionResult(true); }
	/**
	 * @brief	���s���ʂ̍쐬
	*/
	static AssertionResult	Failure(void)	{ return AssertionResult(false); }

private:
	IUTEST_PP_DISALLOW_ASSIGN(AssertionResult);

	::std::string m_message;
	bool	m_result;
};

#if IUTEST_HAS_ASSERTION_RETURN
/**
 * @brief	Assetion Return Type
*/
template<typename R>
struct AssertionReturnType
{
	R value;	//!< �߂�l
	//! �R���X�g���N�^
	AssertionReturnType() {}
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	v : �߂�l�̒l
	*/
	AssertionReturnType(const R& v) : value(v) {}
};
/**
 * @brief	Assetion Return Type (void)
*/
template<>
struct AssertionReturnType<void>
{
	//! �R���X�g���N�^
	AssertionReturnType() {}
};

/**
 * @brief	Assetion Return �ݒ�
*/
template<typename T>
inline AssertionReturnType<T> AssertionReturn(const T& ret) { return AssertionReturnType<T>(ret); }

/** @overload */
inline AssertionReturnType<void> AssertionReturn(void) { return AssertionReturnType<void>(); }

#endif

/**
 * @brief	Assertion �\�z�N���X
*/
class AssertionHelper
{
public:
	/** @private */
	class ScopedMessage : public detail::iu_list_node<ScopedMessage>
		,  public detail::iuCodeMessage
	{
	public:
		ScopedMessage(const detail::iuCodeMessage& msg)
			: detail::iuCodeMessage(msg)
		{
			MessageList::s_scoped_message.push_back(this);
		}
		~ScopedMessage(void)
		{
			MessageList::s_scoped_message.erase(this);
		}
	};
public:
	/** @private */
	typedef detail::iu_list<ScopedMessage> msg_list;

private:
	template<typename T>
	struct List {
		static msg_list s_scoped_message;
	};
	typedef List<void>	MessageList;

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
	friend class ScopedMessage;
#endif

#if IUTEST_HAS_ASSERTION_RETURN
private:
	template<typename R>struct ReturnTypedFixed;
#endif

public:
	/** @private */
	class Fixed : public Message {
	public:
		template<typename T>
		Fixed&		operator << (T val)
		{
			Message::operator << (val);
			return *this;
		}
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
		Fixed&	operator << (iu_basic_iomanip val)
		{
			Message::operator << (val);
			return *this;
		}
#endif

#if IUTEST_HAS_ASSERTION_RETURN
		Fixed&		operator << (const AssertionReturnType<void>&)
		{
			return *this;
		}
		template<typename R>
		ReturnTypedFixed<R> operator << (const AssertionReturnType<R>& ret)
		{
			return ReturnTypedFixed<R>(*this, ret);
		}
#endif
	};

#if IUTEST_HAS_ASSERTION_RETURN
private:
	template<typename R>
	struct ReturnTypedFixed {
		Fixed fixed;
		AssertionReturnType<R> ret;
		ReturnTypedFixed(const Fixed& f, const AssertionReturnType<R>& r) : fixed(f), ret(r) {}
	};
#endif

public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	file	= �t�@�C����
	 * @param [in]	line	= �s�ԍ�
	 * @param [in]	message	= ���b�Z�[�W
	 * @param [in]	type	= �e�X�g���ʂ̃^�C�v
	*/
	AssertionHelper(const char* file, int line, const char* message, TestPartResult::Type type)
		: m_part_result(file, line, message, type)
	{}
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	file	= �t�@�C����
	 * @param [in]	line	= �s�ԍ�
	 * @param [in]	message	= ���b�Z�[�W
	 * @param [in]	type	= �e�X�g���ʂ̃^�C�v
	*/
	AssertionHelper(const char* file, int line, const ::std::string& message, TestPartResult::Type type)
		: m_part_result(file, line, message.c_str(), type)
	{}

private:
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(AssertionHelper);

#if IUTEST_HAS_RVALUE_REFS
	AssertionHelper(AssertionHelper&& rhs) IUTEST_CXX_DELETED_FUNCTION;
	AssertionHelper& operator=(AssertionHelper&&) IUTEST_CXX_DELETED_FUNCTION;
#endif

public:
	/** @private */
	void	operator = (const Fixed& fixed)
	{
		OnFixed(fixed);
#if IUTEST_HAS_EXCEPTIONS && IUTEST_USE_THROW_ON_ASSERT_FAILURE
		{
			if( m_part_result.type() == TestPartResult::kFatalFailure ) throw TestPartResult::kFatalFailure;
		}
#endif
	}
#if IUTEST_HAS_ASSERTION_RETURN
	/** @private */
	template<typename R>
	R	operator = (const ReturnTypedFixed<R>& fixed)
	{
		this->operator=(fixed.fixed);
		return fixed.ret.value;
	}	
#endif

private:
	void	OnFixed(const Fixed& fixed) IUTEST_CXX_NOTHROW
	{
		// OnFixed �� throw ���Ȃ����ƁI�e�X�g���̗�O�L���b�`�ɂ�����Ȃ��Ȃ�

		m_part_result.add_message(fixed.GetString());
		if( MessageList::s_scoped_message.count() )
		{
			m_part_result.add_message("\niutest trace:");
			for( msg_list::iterator it = MessageList::s_scoped_message.begin(), end=MessageList::s_scoped_message.end(); it != end; ++it )
			{
				// TODO : �ǉ����b�Z�[�W�Ƃ��ĕۑ�����ׂ�
				// ����̓e�X�g���ʂ̃��b�Z�[�W�ɒǉ����Ă���B
				m_part_result.add_message("\n");
				m_part_result.add_message(it->make_message().c_str());
			}
		}

		if( TestEnv::GetGlobalTestPartResultReporter() != NULL )
		{
			TestEnv::GetGlobalTestPartResultReporter()->ReportTestPartResult(m_part_result);
		}
		else
		{
			using namespace iutest_report_result;
			ReportTestPartResult(m_part_result);
		}

		if( m_part_result.type() != TestPartResult::kSuccess )
		{
			if( TestFlag::IsEnableFlag(iutest::TestFlag::BREAK_ON_FAILURE) )
			{
				IUTEST_BREAK();
			}
		}
	}

private:
	friend class TestInfo;
	TestPartResult m_part_result;
};

}	// end of namespace iutest

template<typename T>
::iutest::AssertionHelper::msg_list iutest::AssertionHelper::List<T>::s_scoped_message;

namespace iutest
{

//======================================================================
// function
/**
 * @brief	�e�X�g���������� AssertionResult �I�u�W�F�N�g�̎擾
*/
inline AssertionResult	AssertionSuccess(void)	{ return AssertionResult::Success(); }
/**
 * @brief	�e�X�g���s������ AssertionResult �I�u�W�F�N�g�̎擾
*/
inline AssertionResult	AssertionFailure(void)	{ return AssertionResult::Failure(); }

namespace internal
{

/**
 * @brief	��r�e�X�g�̒l�𕶎���Ƀt�H�[�}�b�g
*/
template<typename T1, typename T2>
inline ::std::string FormatForComparisonFailureMessage(const T1& value, const T2& /*other_operand*/)
{
	return PrintToString(value);
}

/**
 * @brief	boolean �e�X�g�̎��s���b�Z�[�W�̏o��
*/
inline ::std::string GetBooleanAssertionFailureMessage(const AssertionResult& ar, const char* expr, const char* actual, const char* expected)
{
	::std::string str = "error: Value of: ";
	str += expr;
	str += "\n  Actual: ";
	str += actual;
	if( !detail::IsEmpty(ar.message()) )
	{
		str += " (";
		str += ar.message();
		str += ")";
	}
	str += "\nExpected: ";
	str += expected;
	return str;
}

/**
 * @brief	Eq �n�A�T�[�V����
*/
inline AssertionResult EqFailure(const char* expected_expression, const char* actual_expression, const char* expected, const char* actual, bool ignoring_case=false)
{
	detail::iuStringStream::type strm;
	strm << "error: Value of " << actual_expression
		<< "\n  Actual: " << actual
		<< "\nExpected: " << expected_expression;
	if( ignoring_case ) strm << " (ignoring case)";
	if( !detail::IsStringEqual(expected_expression, expected) ) strm << "\nWhich is: " << expected;
	return AssertionFailure() << strm.str();
}

/**
 * @private
 * @{
*/
#define DECL_COMPARE_HELPER_I_(op_name, op, type1, type2)									\
	inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelper##op_name(						\
			const char* expr1, const char* expr2, type1 val1, type2 val2) {					\
	if( val1 op val2 ) return AssertionSuccess();											\
	else {																					\
	return AssertionFailure() << "error: Expected: " << expr1 << " " #op " " << expr2		\
		<< "\n  Actual: " << FormatForComparisonFailureMessage(val1, val2)					\
		<< " vs " << FormatForComparisonFailureMessage(val2, val1);							\
	}																						\
	}																						\

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

#define DECL_COMPARE_HELPER_(op_name, op)							\
	template<typename T1, typename T2>								\
	DECL_COMPARE_HELPER_I_(op_name, op, const T1&, const T2&)		\
	DECL_COMPARE_HELPER_I_(op_name, op, BiggestInt, BiggestInt)

#else

#define DECL_COMPARE_HELPER_(op_name, op)							\
	template<typename T1, typename T2>								\
	DECL_COMPARE_HELPER_I_(op_name, op, const T1&, const T2&)

#endif

DECL_COMPARE_HELPER_(NE, !=)
DECL_COMPARE_HELPER_(LE, <=)
DECL_COMPARE_HELPER_(LT, < )
DECL_COMPARE_HELPER_(GE, >=)
DECL_COMPARE_HELPER_(GT, > )

#undef DECL_COMPARE_HELPER_I_
#undef DECL_COMPARE_HELPER_

/**
 * @}
*/

template<typename T>
inline AssertionResult	CmpHelperNull(const char* expr, const T* val)
{
	if( NULL == val ) return AssertionSuccess();

	return AssertionFailure() << "error: Value of " << expr
		<< "\n  Actual: " << val
		<< "\nExpected: NULL";
}

template<typename T>
inline AssertionResult	CmpHelperNotNull(const char* expr, const T* val)
{
	if( NULL != val ) return AssertionSuccess();

	return AssertionFailure() << "error: Value of " << expr
		<< "\n  Actual: NULL\nExpected: not NULL";
}

template<typename T1, typename T2>
inline AssertionResult	CmpHelperSame(const char* expected_str, const char* actual_str
									  , const T1& expected, const T2& actual)
{
	if( &expected == &actual ) return AssertionSuccess();

	return AssertionFailure() << "error: Expected: &(" << expected_str << ") == &(" << actual_str
		<< ")\n  Actual: " << FormatForComparisonFailureMessage(&expected, &actual)
		<< " vs " << FormatForComparisonFailureMessage(&actual, &expected);
}

template<typename T1, typename T2>
inline AssertionResult CmpHelperEQ(const char* expected_str, const char* actual_str
	, const T1& expected, const T2& actual)
{
	IUTEST_UNUSED_VAR(expected_str);

IUTEST_PARGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()

	if( actual == expected ) return AssertionSuccess();

	return EqFailure(expected_str, actual_str
		, FormatForComparisonFailureMessage(expected, actual).c_str()
		, FormatForComparisonFailureMessage(actual, expected).c_str()
		);

IUTEST_PARGMA_WARN_POP()
}

/**
 * @brief	Equal Helper
 * @tparam	IsNullLiteral	= val1 �� NULL ���e�������ǂ���
*/
template<bool IsNullLiteral>
class EqHelper
{
public:
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
	{
		return CmpHelperEQ(expr1, expr2, val1, val2);
	}
};

/**
 * @brief	EqHelper ���ꉻ
*/
template<>
class EqHelper<true>
{
public:
#if !defined(IUTEST_NO_SFINAE)
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2
		, typename detail::enable_if< !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value)
	{
		return CmpHelperEQ(expr1, expr2, val1, val2);
	}
	template<typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, detail::IsNullLiteralHelper::Object* val1, T2* val2)
	{
		IUTEST_UNUSED_VAR(val1);
		return CmpHelperEQ(expr1, expr2, static_cast<T2*>(NULL), val2);
	}
#else
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
	{
		return CmpHelperEQ(expr1, expr2, (T2)val1, val2);
	}
#endif
};

/**
 * @brief	Not Equal Helper
 * @tparam	IsNullLiteral	= val1 �� NULL ���e�������ǂ���
*/
template<bool IsNullLiteral>
class NeHelper
{
public:
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
	{
		return CmpHelperNE(expr1, expr2, val1, val2);
	}
};

/**
 * @brief	NeHelper ���ꉻ
*/
template<>
class NeHelper<true>
{
public:
#if !defined(IUTEST_NO_SFINAE)
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2
		, typename detail::enable_if< !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value)
	{
		return CmpHelperNE(expr1, expr2, val1, val2);
	}
	template<typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, detail::IsNullLiteralHelper::Object* val1, T2* val2)
	{
		IUTEST_UNUSED_VAR(val1);
		return CmpHelperNE(expr1, expr2, static_cast<T2*>(NULL), val2);
	}
#else
	template<typename T1, typename T2>
	static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
	{
		return CmpHelperNE(expr1, expr2, (T2)val1, val2);
	}
#endif
};

template<typename RawType>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNearFloatingPoint(const char* expr1, const char* expr2, const char* absc
													, RawType val1, RawType val2, RawType abs_v)
{
	RawType diff = val1 > val2 ? val1 - val2 : val2 - val1;
	if( diff < abs_v ) return AssertionSuccess();
	floating_point<RawType> f1(diff), f2(abs_v);
	if( f1.AlmostEquals(f2) ) return AssertionSuccess();
	return AssertionFailure() << "error: Value of: abs(" << expr1 << " - " << expr2 << ") <= " << absc
		<< "\n  Actual: abs(" << val1 << " - " << val2 << ") : " << diff
		<< "\nExpected: " << FormatForComparisonFailureMessage(abs_v, diff) ;
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ DoubleNearPredFormat(const char* expr1, const char* expr2, const char* absc
													, double val1, double val2, double abs_v)
{
	return CmpHelperNearFloatingPoint(expr1, expr2, absc, val1, val2, abs_v);
}
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
template<typename T, typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(const char* expr1, const char* expr2, const char* absc
													, const T& val1, const T& val2, const A& abs_v)
{
	T diff = val1 > val2 ? val1 - val2 : val2 - val1;
	if( diff <= abs_v ) return AssertionSuccess();
	return AssertionFailure() << "error: Value of: abs(" << expr1 << " - " << expr2 << ") <= " << absc
		<< "\n  Actual: abs(" << val1 << " - " << val2 << ") : " << diff << "\nExpected: " << FormatForComparisonFailureMessage(abs_v, diff) ;
}
template<typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(const char* expr1, const char* expr2, const char* absc
													, double val1, double val2, const A& abs_v)
{
	return CmpHelperNearFloatingPoint<double>(expr1, expr2, absc, val1, val2, static_cast<double>(abs_v));
}
#endif
template<typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(const char* expr1, const char* expr2, const char* absc
													, float val1, float val2, const A& abs_v)
{
	return CmpHelperNearFloatingPoint<float>(expr1, expr2, absc, val1, val2, static_cast<float>(abs_v));
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
							   , const char* val1, const char* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	else
	{
		if( strcmp(val1, val2) == 0 ) return AssertionSuccess();
	}
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
							   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	else
	{
		if( wcscmp(val1, val2) == 0 ) return AssertionSuccess();
	}
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	if( val1 == val2 ) return AssertionSuccess();
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	if( val2 == val1 ) return AssertionSuccess();
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	if( val1 == val2 ) return AssertionSuccess();
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}
#if IUTEST_HAS_CHAR16_T
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
															   , const char16_t* val1, const char16_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	::std::u16string v1 = val1;
	return CmpHelperSTREQ(expr1, expr2, v1, val2);
}
#endif
#if IUTEST_HAS_CHAR32_T
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
															   , const char32_t* val1, const char32_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	::std::u32string v1 = val1;
	return CmpHelperSTREQ(expr1, expr2, v1, val2);
}
#endif

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
							   , const char* val1, const char* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	else
	{
		if( strcmp(val1, val2) != 0 ) return AssertionSuccess();
	}
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
							   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	else
	{
		if( wcscmp(val1, val2) != 0 ) return AssertionSuccess();
	}
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
															   , const ::std::basic_string<Elem, Traits, Ax>& val1
															   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	if( val1 != val2 ) return AssertionSuccess();
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
															   , const Elem* val1
															   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	if( val2 != val1 ) return AssertionSuccess();
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
															   , const ::std::basic_string<Elem, Traits, Ax>& val1
															   , const Elem* val2)
{
	if( val1 != val2 ) return AssertionSuccess();
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
#if IUTEST_HAS_CHAR16_T
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
															   , const char16_t* val1, const char16_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	::std::u16string v1 = val1;
	return CmpHelperSTRNE(expr1, expr2, v1, val2);
}
#endif
#if IUTEST_HAS_CHAR32_T
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
															   , const char32_t* val1, const char32_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	::std::u32string v1 = val1;
	return CmpHelperSTRNE(expr1, expr2, v1, val2);
}
#endif

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
							   , const char* val1, const char* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	else
	{
		if( detail::iu_stricmp(val1, val2) == 0 ) return AssertionSuccess();
	}
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str()
		, true);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
							   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	else
	{
		if( detail::iu_wcsicmp(val1, val2) == 0 ) return AssertionSuccess();
	}
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str()
		, true);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
							   , const char* val1, const char* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	else
	{
		if( detail::iu_stricmp(val1, val2) != 0 ) return AssertionSuccess();
	}
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2 << " (ignoring case)"
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
							   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	else
	{
		if( detail::iu_wcsicmp(val1, val2) != 0 ) return AssertionSuccess();
	}
	return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2 << " (ignoring case)"
		<< "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
		<< " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2);
}


template<typename RawType>
static AssertionResult CmpHelperFloatingPointEQ(const char* expr1, const char* expr2
							   , RawType val1, RawType val2)
{
	floating_point<RawType> f1(val1), f2(val2);
	if( f1.AlmostEquals(f2) ) return AssertionSuccess();
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}

template<typename RawType>
static AssertionResult	CmpHelperFloatingPointLE(const char* expr1, const char* expr2
							   , RawType val1, RawType val2)
{
	if( val1 < val2 ) return AssertionSuccess();
	floating_point<RawType> f1(val1), f2(val2);
	if( f1.AlmostEquals(f2) ) return AssertionSuccess();
	return EqFailure(expr1, expr2
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2)).c_str()
		, detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)).c_str() );
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ FloatLE(const char* expr1, const char* expr2
							   , float val1, float val2)
{
	return CmpHelperFloatingPointLE<float>(expr1, expr2, val1, val2);
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ DoubleLE(const char* expr1, const char* expr2
							   , double val1, double val2)
{
	return CmpHelperFloatingPointLE<double>(expr1, expr2, val1, val2);
}

#if defined(IUTEST_OS_WINDOWS)

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ IsHRESULTSuccess(const char* expr, HRESULT hr)
{
	if( SUCCEEDED(hr) ) return AssertionSuccess();
	return AssertionFailure() << "error: Expected: SUCCEEDED(" << expr << ")"
		<< "\n  Actual: " << hr << ": " << detail::win::GetHResultString(hr);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ IsHRESULTFailure(const char* expr, HRESULT hr)
{
	if( FAILED(hr) ) return AssertionSuccess();
	return AssertionFailure() << "error: Expected : FAILED(" << expr << ")"
		<< "\n  Actual: " << hr;
}

#endif

}	// end of namespace internal

}	// end of namespace iutest

#endif
