//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_string.h
 * @brief		iris unit test �����񑀍� �t�@�C��
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
#ifndef INCG_IRIS_iutest_string_H_E22B02D7_E9E7_412c_B609_DC3D9C66895D_
#define INCG_IRIS_iutest_string_H_E22B02D7_E9E7_412c_B609_DC3D9C66895D_

//======================================================================
// include
#if defined(__MWERKS__)
#  define _MBSTATE_T
#endif

#include <string>
#include <wchar.h>
#include <wctype.h>
#include <stdarg.h>
#include <string.h>
#if IUTEST_HAS_STRINGSTREAM
#  if IUTEST_USE_STRSTREAM
#    include <strstream>
#  else
#    include <sstream>
#  endif
#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

//======================================================================
// function
/*
 * ���̂Ƃ���g���Ă��Ȃ�

static char*			xcsstr(char* src, const char* substr)				{ return strstr(src, substr); }
static const char*		xcsstr(const char* src, const char* substr)			{ return strstr(src, substr); }
static char*			xcschr(char* src, char ch)							{ return strchr(src, ch); }
static const char*		xcschr(const char* src, char ch)					{ return strchr(src, ch); }
static int				xcscmp(const char* str1, const char* str2)			{ return strcmp(str1, str2); }
static long				xcstol(const char* src, char** end, int radix)		{ return strtol(src, end, radix); }

static wchar_t*			xcsstr(wchar_t* src, const wchar_t* substr)			{ return wcsstr(src, substr); }
static const wchar_t*	xcsstr(const wchar_t* src, const wchar_t* substr)	{ return wcsstr(src, substr); }
static wchar_t*			xcschr(wchar_t* src, wchar_t ch)					{ return wcschr(src, ch); }
static const wchar_t*	xcschr(const wchar_t* src, wchar_t ch)				{ return wcschr(src, ch); }
static int				xcscmp(const wchar_t* str1, const wchar_t* str2)	{ return wcscmp(str1, str2); }
static long				xcstol(const wchar_t* src, wchar_t** end, int radix){ return wcstol(src, end, radix); }

*/

/**
 * @internal
 * @brief	stricmp
*/
inline int iu_stricmp(const char* str1, const char* str2)
{
#if		defined(_MSC_VER)
	return _stricmp(str1, str2);
#elif	defined(__ARMCC_VERSION) || (defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID))
	return strcasecmp(str1, str2);
#else
	return stricmp(str1, str2);
#endif
}

/**
 * @internal
 * @brief	wcsicmp
*/
inline int iu_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
#if		defined(_MSC_VER)
	return _wcsicmp(str1, str2);
#elif	defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID)
	return wcscasecmp(str1, str2);
#else
	const wchar_t* l = str1;
	const wchar_t* r = str2;
	while(*l)
	{
		wchar_t ul = towupper(*l);
		wchar_t ur = towupper(*r);
		if( ul < ur ) return -1;
		if( ul > ur ) return 1;
		++l;
		++r;
	}
	if( *l < *r ) return -1;
	if( *l > *r ) return 1;
	return 0;
#endif
}

inline IUTEST_CONSTEXPR bool IsEmpty(const char* p) { return p == NULL || *p == '\0'; }
inline IUTEST_CONSTEXPR bool IsSpace(char ch)	{ return ch == ' ' || ch =='\t'; }
inline IUTEST_CONSTEXPR const char*	SkipSpace(const char* p)
{
	return p == NULL ? NULL : (IsSpace(*p) ? SkipSpace(++p) : p);
}
inline IUTEST_CONSTEXPR const char*	FindComma(const char* p)
{
	return (p == NULL || *p == '\0') ? NULL : ((*p == ',') ? p : FindComma(++p));
}
inline bool IsStringEqual(const char* str1, const char* str2) { return strcmp(str1, str2) == 0; }
inline bool IsStringCaseEqual(const char* str1, const char* str2) { return iu_stricmp(str1, str2) == 0; }

inline void StringReplace(std::string& str, char a, const char* to)
{
	std::string::size_type pos = 0;
	while( pos = str.find(a, pos), pos != std::string::npos )
	{
		str.replace(pos, 1, to);
		++pos;
	}
}

inline IUTEST_CONSTEXPR char ToHex(unsigned int n) { return (n&0xF) >= 0xA ? 'A'+((n&0xF)-0xA) : '0'+(n&0xF); }

inline std::string ShowStringQuoted(const char* str) { std::string s = "\""; s += str; s += "\""; return s; }
inline std::string ShowStringQuoted(const std::string& str) { std::string s = "\""; s += str; s += "\""; return s; }

//======================================================================
// class
class iuStringStream
{
public:
#if IUTEST_HAS_STRINGSTREAM
#  if IUTEST_USE_STRSTREAM
	class stlstream : public std::strstream
	{
		CHAR buf[256];
	public:
		stlstream(void)
			: std::strstream(buf, 254, std::ios::out)
		{}
	public:
		std::string str(void)
		{
			*this << std::ends;
			std::string str = std::strstream::str();
			return str;
		}
	};
#  else
	typedef std::stringstream	stlstream;
#  endif
#else
	template<class _Elem, class _Traits>class iu_basic_stream;
	typedef iu_basic_stream<char, std::char_traits<char> >			iu_stream;
	typedef iu_basic_stream<wchar_t, std::char_traits<wchar_t> >	iu_wstream;
#endif

public:

#if IUTEST_HAS_STRINGSTREAM
	typedef stlstream	type;
#else
	typedef iu_stream	type;
#endif


public:

#if !IUTEST_HAS_STRINGSTREAM

	template<typename T>
	struct xcs
	{
	private:
		template<typename TMP, typename TN>
		struct impl_select
		{
			template<typename TA, typename TB>
			static const TA	constant(const TA a, const TB b)
			{
				(void)b;
				return a;
			}
		};
		template<typename TMP>
		struct impl_select<TMP, wchar_t>
		{
			template<typename TA, typename TB>
			static const TB	constant(const TA a, const TB b)
			{
				(void)a;
				return b;
			}
		};

	public:
		typedef impl_select<void, T>	select;
	};
#define IUTEST_PP_XCS(txt_)	xcs<_Elem>::select::constant(txt_, L##txt_)

	template<class _Elem, class _Traits>
	class iu_basic_stream
	{
		typedef iu_basic_stream<_Elem, _Traits>			_Myt;
		//typedef std::basic_streambuf<_Elem, _Traits>	streambuf;
		//typedef std::basic_ostream<_Elem, _Traits>	ostream;
		typedef std::basic_string<_Elem, _Traits>		string;
		string s;

		struct impl
		{
			template<typename E>
			static int vastring(E* dst, const E* fmt, va_list va);
			static int vastring(char* dst, size_t len, const char* fmt, va_list va)
			{
				(void)len;
				return vsprintf(dst, fmt, va);
			}
			static int vastring(wchar_t* dst, size_t len, const wchar_t* fmt, va_list va)
			{
				return vswprintf(dst, len, fmt, va);
			}

			template<typename E>
			static int tostring(E* dst, size_t len, const E* fmt, ...)
			{
				va_list va;
				va_start(va, fmt);
				int ret = vastring(dst, len, fmt, va);
				va_end(va);
				return ret;
			}
		};
	public:
		iu_basic_stream(void) {}
	public:

		inline _Myt& operator<< (char v)
		{
			s += v;
			return *this;
		}
		inline _Myt& operator<< (signed char v)
		{
			s += (char)v;
			return *this;
		}
		inline _Myt& operator<< (unsigned char v)
		{
			s += (char)v;
			return *this;
		}
		inline _Myt& operator<< (const _Elem* v)
		{
			s += v;
			return *this;
		}
		//inline _Myt& operator<< (const signed _Elem* v)
		//{
		//	s += v;
		//	return *this;
		//}
		//inline _Myt& operator<< (const unsigned _Elem* v)
		//{
		//	s += v;
		//	return *this;
		//}
		inline _Myt& operator<< (bool v)
		{
#if 0
			_Elem a[16];
			impl::tostring(a, 16, IUTEST_PP_XCS("%i"), v);
			s += a;
#else
			s += (v ? IUTEST_PP_XCS("true") : IUTEST_PP_XCS("false"));
#endif
			return *this;
		}
		inline _Myt& operator<< (short v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%i"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (unsigned short v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%u"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (int v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%i"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (unsigned int v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%u"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (long v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%i"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (unsigned long v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%u"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (long long int v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%ll"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (unsigned long long int v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%llu"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (float v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%f"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (double v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%l"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (long double v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%L"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (const void* v)
		{
			_Elem a[64];
			impl::tostring(a, 64, IUTEST_PP_XCS("%t"), v);
			s += a;
			return *this;
		}
		inline _Myt& operator<< (const std::string& v)
		{
			s += v;
			return *this;
		}
	public:
		const string& str(void) const { return s; }
	};

#undef IUTEST_PP_XCS

#endif
};

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}	// end of namespace detail
}	// end of namespace iutest

#endif
