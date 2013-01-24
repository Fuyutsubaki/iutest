//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_stream.hpp
 * @brief		iris unit test io stream ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_stream_HPP_3A4AF139_9F24_4730_81D0_DADFCE6DCF99_
#define INCG_IRIS_iutest_stream_HPP_3A4AF139_9F24_4730_81D0_DADFCE6DCF99_

//======================================================================
// include

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	出力ストリームインターフェイス
*/
class IOutStream
{
public:
	virtual ~IOutStream(void) {}
public:
	//! 書き込み
	virtual void	Write(const void* buf, size_t size, size_t cnt) = 0;
public:
	virtual void	Printf(const char* fmt, ...)
	{
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

		// TODO : Fixed buffer...
		char buf[1024] = {0};
		va_list va;
		va_start(va, fmt);
#ifdef _MSC_VER
		_vsnprintf(buf, sizeof(buf), fmt, va);
#else
		vsnprintf(buf, sizeof(buf), fmt, va);
#endif
		va_end(va);

		const size_t len = strlen(buf);
		Write(buf, len, 1);

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
	}
};

/**
 * @brief	ファイルIO出力ストリームインターフェイス
*/
class FileOutStream : public IOutStream
{
protected:
	FILE*	m_fp;
public:
	FileOutStream(FILE* fp)
		: m_fp(fp)
	{}
public:
	/**
	 * @brief	書き込み
	 * @param [in]	buf		= 書き込みバッファ
	 * @param [in]	size	= バッファサイズ
	 * @param [in]	cnt		= 書き込み回数
	*/
	virtual void	Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
	{
		fwrite(buf, size, cnt, m_fp);
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
