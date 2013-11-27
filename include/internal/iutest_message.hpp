//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_message.hpp
 * @brief		iris unit test ���b�Z�[�W �t�@�C��
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
#ifndef INCG_IRIS_IUTEST_MESSAGE_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_
#define INCG_IRIS_IUTEST_MESSAGE_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_

//======================================================================
// include
#include "../iutest_env.hpp"
#include "iutest_constant.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// declare
/**
 * @brief	�t�@�C�����ƍs�ԍ���A������������𐶐�(�R���p�C�����l������)
*/
::std::string FormatFileLocation(const char* file, int line);
/**
 * @brief	�t�@�C�����ƍs�ԍ���A������������𐶐�
*/
::std::string FormatCompilerIndependentFileLocation(const char* file, int line);

//======================================================================
// class
/**
 * @brief	���b�Z�[�W�N���X
*/
class iuStreamMessage
{
public:
	iuStreamMessage(void) {}
	explicit iuStreamMessage(const char* message) : m_stream(message) {}
	iuStreamMessage(const iuStreamMessage& rhs) : m_stream(rhs.GetString()) {}

public:
	::std::string GetString(void)	const	{ return m_stream.str(); }
public:
	template<typename T>
	iuStreamMessage&	operator << (const T& value) 
	{
		m_stream << value;
		return *this;
	}
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
	template<typename T>
	iuStreamMessage&	operator << (T* const& value) 
	{
		if( value == NULL ) 
		{
			m_stream << "(null)";
		}
		else
		{
			m_stream << value;
		}
		return *this;
	}
#endif
	iuStreamMessage&	operator << (bool b) 
	{
		m_stream << (b ? "true" : "false");
		return *this;
	}
	iuStreamMessage&	operator << (char* str)
	{
		append(str);
		return *this;
	}
	iuStreamMessage&	operator << (const char* str)
	{
		append(str);
		return *this;
	}
	iuStreamMessage&	operator << (wchar_t* str)
	{
		m_stream << ShowWideCString(str);
		return *this;
	}
	iuStreamMessage&	operator << (const wchar_t* str)
	{
		m_stream << ShowWideCString(str);
		return *this;
	}
	iuStreamMessage&	operator << (const iuStreamMessage& message)
	{
		m_stream << message.GetString();
		return *this;
	}
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
	iuStreamMessage&	operator << (iu_basic_iomanip val)
	{
		m_stream << val;
		return *this;
	}
#endif

public:
	/**
	 * @brief	���b�Z�[�W�̒ǋL
	*/
	void	add_message(const char* str) { append(str); }
private:
	void	append(const char* str);

private:
	iuStreamMessage& operator = (const iuStreamMessage&);

private:
	detail::iuStringStream::type m_stream;
};

inline iu_ostream& operator << (iu_ostream& os, const iuStreamMessage& msg)
{
	return os << msg.GetString();
}

template<typename T>
inline ::std::string StreamableToString(const T& value)
{
	return (iuStreamMessage() << value).GetString();
}

/**
 * @brief	�t�@�C��/���C��/���b�Z�[�W�N���X
*/
class iuCodeMessage
{
	::std::string	m_message;	//!< ���b�Z�[�W
	const char*		m_file;		//!< �t�@�C����
	int				m_line;		//!< ���C��
public:
	iuCodeMessage(const char* file, int line, const char* message)
		: m_message(message)
		, m_file(file ? file : kStrings::UnkownFile)
		, m_line(line)
	{}
	iuCodeMessage(const char* file, int line, const iuStreamMessage& message)
		: m_message(message.GetString())
		, m_file(file ? file : kStrings::UnkownFile)
		, m_line(line)
	{}
public:
	const char*		message(void)	const { return m_message.c_str(); }		//!< ���b�Z�[�W�̎擾
	const char*		file_name(void) const IUTEST_CXX_NOEXCEPT_SPEC { return m_file; }	//!< �t�@�C�����̎擾
	int				line_number(void) const IUTEST_CXX_NOEXCEPT_SPEC { return m_line; }	//!< ���C���ԍ��̎擾


public:
	template<typename T>
	iuCodeMessage&	operator << (const T& value) 
	{
		m_message += StreamableToString(value);
		return *this;
	}

public:
	/**
	 * @brief	���b�Z�[�W�̒ǋL
	*/
	void	add_message(const ::std::string& str);

public:
	/** @private */
	::std::string	make_message(void) const;
	::std::string	make_newline_message(void) const
	{
		return make_message() + "\n";
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_message.ipp"
#endif

#endif
