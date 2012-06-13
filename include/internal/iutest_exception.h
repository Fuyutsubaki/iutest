//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_exception.h
 * @brief		iris unit test exception ��` �t�@�C��
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
#ifndef INCG_IRIS_iutest_exception_H_B73B2E25_97C8_4dfc_BC32_5E53039A1A64_
#define INCG_IRIS_iutest_exception_H_B73B2E25_97C8_4dfc_BC32_5E53039A1A64_

//======================================================================
// include
#include "../iutest_defs.h"

#if IUTEST_HAS_EXCEPTIONS
#include "iutest_string.h"
#include <exception>

namespace iutest {
namespace detail
{

/**
 * @brief	C++��O���b�Z�[�W�̃t�H�[�}�b�g
 * @param [in]	description	= ����
 * @return	���b�Z�[�W
*/
inline std::string FormatCxxException(const char* description)
{
	iuStringStream::type strm;
	if( description != NULL )
	{
		strm << "C++ exception with description \"" << description << "\"";
	}
	else
	{
		strm << "Unknown C++ exception";
	}
	return strm.str();
}

}	// end of namespace detail
}	// end of namespace iutest

#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
#include <iomanip>

namespace iutest {
namespace detail
{

/**
 * @brief	SEH ��O
*/
class seh_exception : public std::exception
{
public:
	seh_exception(const char *const& _What) : std::exception(_What) {}
	seh_exception(void) : std::exception() {}
	~seh_exception(void) {}
public:
	static void	translator(DWORD code, _EXCEPTION_POINTERS* ep)
	{
		IUTEST_UNUSED_VAR(ep);
		iuStringStream::type strm;
		strm << "SEH exception with code 0x" << std::setbase(16) << code << std::setbase(10);
		throw seh_exception(strm.str().c_str());
	}
	static int should_process_through_break_and_cppexceptions(DWORD code)
	{
		bool should_handle = true;
		// break point �� C++ ��O�̓n���h�����O���Ȃ�
		if( code == EXCEPTION_BREAKPOINT )
			should_handle = false;
		if( code == kCxxExceptionCode )
			should_handle = false;
		return should_handle ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
	}
public:
	static const int kCxxExceptionCode = 0xe06d7363;	//!< c++ exception �R�[�h
};

}	// end of namespace detail
}	// end of namespace iutest

#endif

#endif

#endif
