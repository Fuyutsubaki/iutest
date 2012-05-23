//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_defs.h
 * @brief		iris unit test ��` �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_defs_H_839F06DB_E0B6_4e6a_84F2_D99C0A44E06C_
#define INCG_IRIS_iutest_defs_H_839F06DB_E0B6_4e6a_84F2_D99C0A44E06C_

//======================================================================
// include
#include "internal/iutest_compiler.h"
#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * @defgroup	IUTEST_CONFIG	IUTEST_CONFIG
 * @brief		�ݒ�}�N��
 * @note		���[�U�[�����O��`���邱�ƂŕύX�\
 * @{
*/

#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)	vprintf(f, a)	//!< vprintf �Ăяo���}�N��
#endif

#ifndef IUTEST_PRINTF
#  define IUTEST_PRINTF			printf			//!< printf �Ăяo���}�N��
#endif

// support
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
//! iutest::Combine ���d�l�g�p�\���ǂ���
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_COMBINE		1
#  else
#    define IUTEST_HAS_COMBINE		0
#  endif
#endif

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

#ifndef IUTEST_HAS_GENRAND
#  define IUTEST_HAS_GENRAND		1	//!< �e�X�g���Ƃ� genrand �֐����g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_FOPEN
#  define IUTEST_HAS_FOPEN			1	//!< fopen ���g�p�\���ǂ���
#endif

#ifndef IUTEST_HAS_CTIME
#  if	defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_CTIME		0	//!< time �֐����g�p�\���ǂ���
#  else
#    define IUTEST_HAS_CTIME		1	//!< time �֐����g�p�\���ǂ���
#  endif
#endif

#ifndef IUTEST_HAS_STRINGSTREAM
#  define IUTEST_HAS_STRINGSTREAM	1	//!< std::stringstream ���g�p�\���ǂ���
#endif

#ifndef IUTEST_USE_STRSTREAM
#  define IUTEST_USE_STRSTREAM		0	//!< std::strstream ���g�p�\���ǂ���
#endif

#ifndef IUTEST_THROW_ON_ASSERT_FAILURE
/**
 * @brief	ASSERT �}�N���Ŏ��s���ɗ�O�� throw ���܂��B
 * @note	�T�u�֐��ɃA�T�[�V�������L�q���Ă��A���̎��_�Ńe�X�g�����f�����悤�ɂȂ�܂�
*/
#  define IUTEST_THROW_ON_ASSERT_FAILURE	IUTEST_HAS_EXCEPTIONS
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

#if defined(_IUTEST_DEBUG)
#include "internal/iutest_debug.h"
#endif

namespace iutest
{

//======================================================================
// struct
namespace detail
{

/**
 * @brief	type_least_t
*/
template<int SIZE>
struct type_least_t {};

/** type_least_t<1> */
template<>
struct type_least_t<1>
{
	typedef char				Int;
	typedef unsigned char		UInt;
};

/** type_least_t<2> */
template<>
struct type_least_t<2>
{
	typedef short				Int;
	typedef unsigned short		UInt;
};

/** type_least_t<4> */
template<>
struct type_least_t<4>
{
	typedef int					Int;
	typedef unsigned int		UInt;
};

/** type_least_t<8> */
template<>
struct type_least_t<8>
{
#if defined(_MSC_VER)
	typedef __int64				Int;
	typedef unsigned __int64	UInt;
#else
	typedef long long			Int;
	typedef unsigned long long	UInt;
#endif
};

}

/**
 * @brief	���������_��
*/
template<typename RawType>
class floating_point
{
private:
	typedef floating_point<RawType>	_Myt;

	template<typename T, typename DMY>
	struct impl				 { typedef detail::type_least_t<4>	type; };
	template<typename DMY>
	struct impl<double, DMY> { typedef detail::type_least_t<8>	type; };

	typedef typename impl<RawType, void>::type	type;
	typedef typename type::Int	Int;
	typedef typename type::UInt	UInt;
	union FInt
	{
		Int		iv;
		UInt	uv;
		RawType	fv;
	};

public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	f	= ���������_��
	*/
	floating_point(RawType f)
	{
		m_v.fv = f;
	}

public:
	/**
	 * @brief	���������_�����قڈ�v���邩�ǂ���
	 * @note	http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
	*/
	bool	AlmostEquals(const _Myt& rhs) const
	{
		const Int v1 = m_v.iv < 0 ? ~m_v.iv + 1 : m_v.iv;
		const Int v2 = rhs.m_v.iv < 0 ? ~rhs.m_v.iv + 1 : rhs.m_v.iv;
		const Int diff = (v1 > v2) ? v1 - v2 : v2 - v1;
		if( diff <= kMaxUlps ) return true;
		return false;
	}

private:
	static const Int	kMaxUlps = 4;
private:
	FInt	m_v;
};

namespace internal
{

typedef void*	TypeId;		//!< �e�X�g���ʌ^

namespace helper
{

//======================================================================
// struct
/**
 * @brief	TypeId Generator Implementation
*/
template<typename TN>
struct TestTypeIdHelper { public: static bool _dummy; };

template<typename TN>bool TestTypeIdHelper<TN>::_dummy = false;

}

//======================================================================
// function
/**
  * @internal
  * @brief	TypeId Generator
*/
template<typename TN>
inline IUTEST_CONSTEXPR TypeId	GetTypeId(void)
{
	return &(helper::TestTypeIdHelper<TN>::_dummy);
}

/**
  * @internal
  * @brief	TypeId Generator
*/
inline IUTEST_CONSTEXPR TypeId	GetTestTypeId(void)
{
	return 0;
}

}

//======================================================================
// typedef
typedef detail::type_least_t<4>::Int	Int32;	//!< 32 bit �����t�������^
typedef detail::type_least_t<4>::UInt	UInt32;	//!< 32 bit �����Ȃ������^
typedef detail::type_least_t<8>::Int	Int64;	//!< 64 bit �����t�������^
typedef detail::type_least_t<8>::UInt	UInt64;	//!< 64 bit �����Ȃ������^

typedef internal::TypeId TestTypeId;	//!< �e�X�g���ʌ^

typedef void (*SetUpMethod)(void);		//!< SetUp �֐��^
typedef void (*TearDownMethod)(void);	//!< TearDown �֐��^

typedef detail::type_least_t<8>::UInt	TimeInMillisec;	//!< �~���b�P�ʂ������^
typedef detail::type_least_t<8>::Int	BiggestInt;		//!< Biggest Int

}	// end of namespace iutest

#endif
