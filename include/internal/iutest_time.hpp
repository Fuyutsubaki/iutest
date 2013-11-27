//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_time.hpp
 * @brief		iris unit test time utility �t�@�C��
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
#ifndef INCG_IRIS_IUTEST_TIME_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
#define INCG_IRIS_IUTEST_TIME_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include <time.h>

#if IUTEST_HAS_CXX11_HDR_CHRONO
#  include <chrono>
#endif

#if		IUTEST_HAS_HDR_SYSTIME
#  include <sys/time.h>
#elif	defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <sys/timeb.h>
#endif

namespace iutest {
namespace detail
{

//======================================================================
// declare
/**
  * @internal
  * @brief	TimeInMillisec to string
  * @param	[in]	msec	= �~���b
  * @return	�b���̕�����
*/
::std::string	FormatTimeInMillisecAsSecond(TimeInMillisec msec);

/**
  * @internal
  * @brief	TimeInMillisec to string
  * @param	[in]	msec	= �~���b
  * @return	�����̕�����
*/
::std::string	FormatTimeInMillisecAsIso8601(TimeInMillisec msec);

/**
 * @brief	���ݎ����̎擾
*/
time_t			GetTime(void);

/**
 * @brief	���ݎ����̃~���b�擾
*/
TimeInMillisec	GetTimeInMillis(void);

/**
 * @brief	�s��Ȓl�̎擾
*/
unsigned int	GetIndefiniteValue(void);

//======================================================================
// class
/**
 * @internal
 * @brief	�X�g�b�v�E�H�b�`�N���X
*/
class iuStopWatch
{
private:
	TimeInMillisec	m_begin;
public:
	iuStopWatch(void) : m_begin(0)	{}

public:
	// ���݂̎��Ԃ��~���b�P�ʂŎ擾
	static TimeInMillisec	get_millisec(void)
	{
#if		defined(IUTEST_NOT_SUPPORT_STOPWATCH)
		return 0;
#else
		return GetTimeInMillis();
#endif
	}
public:
	void			start(void)
	{
		m_begin = get_millisec();
	}
	TimeInMillisec	stop(void) const
	{
		return get_millisec() - m_begin;
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_time.ipp"
#endif

#endif
