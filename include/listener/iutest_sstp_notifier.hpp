//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_sstp_notifier.hpp
 * @brief		iris unit test SSTP �ʒm �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_sstp_notifier_HPP_1187A63F_E99B_4289_A562_3C87B9739B7D_
#define INCG_IRIS_iutest_sstp_notifier_HPP_1187A63F_E99B_4289_A562_3C87B9739B7D_

//======================================================================
// include
#include "../iutest_core.hpp"

#if IUTEST_HAS_STREAM_RESULT
#include "../internal/iutest_socket.hpp"

namespace iutest
{

//======================================================================
// class
namespace detail
{

/**
 * @brief	SSTP
*/
class SSTP : public Socket
{
public:
	enum eCharset
	{
		CHARSET_ASCII
		, CHARSET_SHIFTJIS
		, CHARSET_ISO_220_JP
		, CHARSET_EUC_JP
		, CHARSET_UTF8
	};
	enum eOption
	{
		  OPTION_NODESCRIPT	= 0x0001
		, OPTION_NOTRANSLATE= 0x0002
	};
	static const int DEFAULT_PORT=9801;

private:
	class Response
	{
	public:
		::std::string m_message;
		int m_major;
		int m_minor;
		int m_code;
	public:
		template<size_t N>
		Response(const char (&str)[N])
			: m_major(0), m_minor(0), m_code(0)
		{
			Parse(str);
		}
	public:
		template<size_t N>
		bool Parse(const char (&str)[N])
		{
			m_code = -1;
			if( !detail::IsStringForwardMatching(str, "SSTP/") ) {
				return false;
			}
			char* p=NULL;
			m_major = strtol(str+5, &p, 10);
			m_minor = strtol(p+1, &p, 10);
			m_code = strtol(p+1, &p, 10);
			m_message = p;
			return true;
		}
	};
public:
	explicit SSTP(const ::std::string& sender, eCharset charset=CHARSET_SHIFTJIS)
		: m_Sender(sender), m_Charset(charset), m_bInitialOpen(false) {}

public:
	bool Open(const char* host, const char* port)
	{
		m_Host = host;
		m_Port = port;
		m_bInitialOpen = Socket::Open(host, port);
		return m_bInitialOpen;
	}
public:
	SSTP& Notify(void)
	{
		if( m_bInitialOpen && Socket::Open(m_Host.c_str(), m_Port.c_str()) )
		{
			SendLn("NOTIFY SSTP/1.1");
			SendLn("Sender: " + m_Sender);
			SendLn("Charset: " + FormatCharset(m_Charset));
		}
		return *this;
	}
	SSTP& End(void)
	{
		SendLn("");
		Recv();
		Close();
		return *this;
	}
public:
	SSTP& Event(const ::std::string& id)
	{
		SendLn("Event: " + id);
		return *this;
	}
	SSTP& Reference(int index, const ::std::string& info)
	{
		SendLn("Reference" + detail::StreamableToString(index) + ": " + info);
		return *this;
	}
	SSTP& Script(const ::std::string& script)
	{
		SendLn("Script: " + MultiByteStringToUTF8(script.c_str()));
		return *this;
	}
	SSTP& Option(eOption option)
	{
		SendLn("Option: " + FormatOption(option));
		return *this;
	}
	SSTP& Locale(const ::std::string& locale)
	{
		SendLn("Locale: " + locale);
		return *this;
	}
	SSTP& Marker(const ::std::string& maker)
	{
		SendLn("Marker: " + maker);
		return *this;
	}
	SSTP& Entry(const ::std::string& entry)
	{
		SendLn("Entry: " + entry);
		return *this;
	}
	SSTP& Hwnd(UInt32 hWnd)
	{
		SendLn("HWnd: " + detail::StreamableToString(hWnd));
		return *this;
	}
	SSTP& IfGhost(const ::std::string& ghost)
	{
		SendLn("IfGhost: " + ghost);
		return *this;
	}
private:
	void Recv(void)
	{
		char buf[1024];
		if( Read(buf, sizeof(buf)) )
		{
#if defined(_IUTEST_DEBUG)
			puts(buf);
#endif
			Response res(buf);
			if( res.m_code < 200
				|| res.m_code >= 300 )
			{
				IUTEST_LOG_(WARNING) << buf;
			}
		}
	}
private:
	::std::string FormatCharset(eCharset charset)
	{
		switch (charset)
		{
		case CHARSET_ASCII:
		default:
			return "ASCII";
		case CHARSET_SHIFTJIS:
			return "Shift_JIS";
		case CHARSET_ISO_220_JP:
			return "ISO-2022-JP";
		case CHARSET_EUC_JP:
			return "EUC-JP";
		case CHARSET_UTF8:
			return "UTF-8";
		}
	}
	::std::string FormatOption(eOption option)
	{
		::std::string str="";
		if( option & OPTION_NODESCRIPT )
		{
			str += "nodescript";
		}
		if( option & OPTION_NOTRANSLATE )
		{
			if( !str.empty() ) str += ",";
			str += "notranslate";
		}
		return "";
	}
private:
	::std::string m_Sender;
	::std::string m_Host;
	::std::string m_Port;
	eCharset m_Charset;
	bool m_bInitialOpen;
};

}	// end of namespace detail

namespace ukagaka
{

/**
 * @brief	Sakura script
*/
class SakuraScript
{
public:
	SakuraScript(void) {}
	SakuraScript(const char* script) : m_script(script) {}
	SakuraScript(const ::std::string& script) : m_script(script) {}
public:
	SakuraScript& Append(const std::string& str)
	{
		m_script.append(str);
		return *this;
	}
	template<typename T>
	SakuraScript& Append(const T& v)
	{
		m_script.append(detail::StreamableToString(v));
		return *this;
	}

public:
	SakuraScript& Surface(int id) { Append("\\s[" + detail::StreamableToString(id) + "]"); return *this; }
	SakuraScript& Animate(int id) { Append("\\i[" + detail::StreamableToString(id) + "]"); return *this; }
	SakuraScript& Concat(void) { m_script.insert(0, "\\C"); return *this; }
	SakuraScript& Ln(void) { Append("\\n"); return *this; }
	SakuraScript& Home(void) { Append("\\h"); return *this; }
	SakuraScript& You(void) { Append("\\u"); return *this; }
	SakuraScript& Scope(int id) { Append("\\p[" + detail::StreamableToString(id) + "]"); return *this; }
	SakuraScript& Quick(void) { Append("\\_q"); return *this; }

	SakuraScript& Open(const ::std::string& file) { Append("\\![open,file," + file + "]"); return *this; }

public:
	const ::std::string& ToString(void) 
	{
		// ���s�͉��s�^�O�ɕύX����
		detail::StringReplace(m_script, '\n', "\\n");
		return m_script;
	}

public:
	SakuraScript& operator + (const ::std::string& str)
	{
		return Append(str);
	}
	template<typename T>
	SakuraScript& operator + (const T& v)
	{
		return Append(v);
	}

private:
	::std::string m_script;
};

namespace ghost
{

/**
 * @brief	emily4
*/
struct Emily4
{
	enum 
	{
		  Normal = 0		//!< �ʏ�
		, Shy				//!< �Ƃ�
		, Surprise			//!< ����
		, Anxiety			//!< �s��
		, Shocke			//!< �͂��[
		, Smile				//!< ��
		, EyesClose			//!< �ڕ�
		, Angry				//!< �{��
		, BitterSmile		//!< ��΂�
		, AngerToCoverEmbarrassment	//!< �Ƃ�{��
		, Fidget = 21		//!< ��������
		//, Exhilarated = 25	//!< ��́[
		, Question			//!< �^��
		, Derision			//!< ���
		, ShyEyesClose = 31	//!< �Ƃ�ڕ�
		, Blubber = 34		//!< �������Ⴍ��
		, Explosion = 40	//!< ����
		, Thoughtful = 127	//!< �l������
	};

	struct Skill
	{
		enum
		{
			  TypeA = 24	//!< ���@����
			, TypeB = 124	//!< ���@����/�ڕ�
			, TypeC = 1024	//!< ���@����/���@�w�Ȃ�
			, TypeD = 1124	//!< ���@����/���@�w�Ȃ�/�ڕ�
		};
	};

	struct Doll
	{
		enum
		{
			Todo = 20		//!< TODO�l�`
		};
	};

	struct Coock
	{
		enum
		{
			  Shy = 51		//!< �Ƃ�
			, Anxiety = 53	//!< �s��
			, Smile = 55	//!< ��
			, EyesClose		//!< �ڕ�
		};
	};
};

}

}	// end of namespace ukagaka

/**
 * @brief	SSTP notifier
*/
class SSTPNotifier : public EmptyTestEventListener
{
	typedef ukagaka::SakuraScript	Script;
	typedef ukagaka::ghost::Emily4	Ghost;
public:
	SSTPNotifier(const char* host, int port=detail::SSTP::DEFAULT_PORT);

public:
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestIterationStart(const UnitTest& test
									, int iteration) IUTEST_CXX_OVERRIDE;
	virtual void OnTestCaseStart(const TestCase& test_case) IUTEST_CXX_OVERRIDE;
	virtual void OnTestStart(const TestInfo& test_info) IUTEST_CXX_OVERRIDE;
	virtual void OnTestPartResult(const TestPartResult& test_part_result) IUTEST_CXX_OVERRIDE;
	virtual void OnTestRecordProperty(const TestProperty& test_property) IUTEST_CXX_OVERRIDE;
	virtual void OnTestEnd(const TestInfo& test_info) IUTEST_CXX_OVERRIDE;
	virtual void OnTestCaseEnd(const TestCase& test_case) IUTEST_CXX_OVERRIDE;
	virtual void OnTestIterationEnd(const UnitTest& test
									, int iteration) IUTEST_CXX_OVERRIDE;
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

private:
	::std::string FormatMessage(const ::std::string& path);
	::std::string FormatPath(const ::std::string& path);
	::std::string FormatBool(bool b);
private:
	detail::SSTP m_sstp;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(SSTPNotifier);
};

//======================================================================
// function
//! ProgressPrintListener �ɐ؂�ւ�
inline void SetUpSSTPNotifier(const char* host, int port=detail::SSTP::DEFAULT_PORT)
{
	::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
	listeners.Append(new SSTPNotifier(host, port));
}

}	// end of namespace iutest

namespace iutest
{

IUTEST_IPP_INLINE SSTPNotifier::SSTPNotifier(const char* host, int port)
	: m_sstp("iutest", detail::SSTP::CHARSET_UTF8)
{
	if( !m_sstp.Open(host, detail::StreamableToString(port).c_str()) )
		IUTEST_LOG_(WARNING) << "SSTPNotifier: failed connect to " << host << ":" << port;
}


IUTEST_IPP_INLINE void SSTPNotifier::OnTestProgramStart(const UnitTest& test)
{
	IUTEST_UNUSED_VAR(test);
	m_sstp.Notify()
		.Script(Script("�e�X�g�X�^�`�g").Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestIterationStart(const UnitTest& test
								  , int iteration)
{
	IUTEST_UNUSED_VAR(test);
	m_sstp.Notify()
		.Script(Script(detail::StreamableToString(iteration+1) + "��ڂ̃e�X�g����").Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestCaseStart(const TestCase& test_case)
{
	m_sstp.Notify()
		.Script(Script().Surface(Ghost::Normal)
			.Append(detail::StreamableToString(test_case.name()) + " �e�X�g�P�[�X���J�n").Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestStart(const TestInfo& test_info)
{
	m_sstp.Notify()
		.Script(Script().Surface(Ghost::Normal)
			.Append(detail::StreamableToString(test_info.name()) + " �e�X�g���J�n").Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestPartResult(const TestPartResult& test_part_result)
{
	const char* filename = test_part_result.file_name();
	if( filename == NULL ) filename = "";

	if( test_part_result.passed() )
	{
	}
	else
	{
		m_sstp.Notify()
			.Script(Script().Surface(Ghost::Anxiety).Append(FormatPath(filename) + "��"
				+ detail::StreamableToString(test_part_result.line_number()) + "�s�ڂŎ��s������\n"
				+ FormatMessage(test_part_result.message())).Concat().Ln().Open(FormatPath(filename)).ToString())
			.End();
	}
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestRecordProperty(const TestProperty& test_property)
{
	m_sstp.Notify()
		.Script(Script("TestRecordProperty:" + detail::StreamableToString(test_property.key())
			+ "=" + test_property.value()).Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestEnd(const TestInfo& test_info)
{
	m_sstp.Notify()
		.Script(Script().Surface(test_info.Passed() ? Ghost::Smile : Ghost::Angry)
			.Append( FormatBool(test_info.Passed()) + "������"
			+ "(" + detail::StreamableToString(test_info.elapsed_time()) + "ms)").Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestCaseEnd(const TestCase& test_case)
{
	m_sstp.Notify()
		.Script(Script( detail::StreamableToString(test_case.name()) + " �e�X�g�P�[�X��"
			+ FormatBool(test_case.Passed()) + "������"
			+ "(" + detail::StreamableToString(test_case.elapsed_time()) + "ms)").Concat().Ln().ToString())
		.End();
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestIterationEnd(const UnitTest& test
								, int iteration)
{
	IUTEST_UNUSED_VAR(test);
	IUTEST_UNUSED_VAR(iteration);
}
IUTEST_IPP_INLINE void SSTPNotifier::OnTestProgramEnd(const UnitTest& test)
{
	IUTEST_UNUSED_VAR(test);
	m_sstp.Notify()
		.Script(Script("�����").Concat().Ln().ToString())
		.End();
	m_sstp.Close();
}

IUTEST_IPP_INLINE ::std::string SSTPNotifier::FormatMessage(const ::std::string& path)
{
	::std::string str = path;
	detail::StringReplace(str, '\\', "/");
	return str;
}

IUTEST_IPP_INLINE ::std::string SSTPNotifier::FormatPath(const ::std::string& path)
{
	::std::string str = path;
	detail::StringReplace(str, '\\', "/");
	return str;
}

IUTEST_IPP_INLINE ::std::string SSTPNotifier::FormatBool(bool b)
{
	if( b ) return "����";
	return "���s";
}

}	// end of namespace iutest

#endif

#endif
