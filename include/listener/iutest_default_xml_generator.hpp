//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_default_xml_generator.hpp
 * @brief		iris unit test xml �o�̓C�x���g���X�i�[ �t�@�C��
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
#ifndef INCG_IRIS_iutest_default_xml_generator_HPP_791DCB98_05CC_49ba_8518_0EC9CA2B5450_
#define INCG_IRIS_iutest_default_xml_generator_HPP_791DCB98_05CC_49ba_8518_0EC9CA2B5450_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	xml�o�̓C�x���g���X�i�[
*/
class DefaultXmlGeneratorListener : public EmptyTestEventListener
{
	::std::string	m_output_path;
	IFile*	m_fp;
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in] path = �o�̓p�X
	*/
	DefaultXmlGeneratorListener(const ::std::string& path)
		: m_fp(NULL)
	{
		SetFilePath(path);
	}
	virtual ~DefaultXmlGeneratorListener(void)
	{
		FileClose();
		TestEnv::event_listeners().set_default_xml_generator(NULL);
	}
public:
	/**
	 * @brief	�o�̓t�@�C���̐ݒ�
	*/
	void	SetFilePath(const ::std::string& path)
	{
		if( path.empty() )
		{
			m_output_path = detail::kStrings::DefaultXmlReportFileName;
		}
		else
		{
			m_output_path = path;
			if( path.find('.') == ::std::string::npos )
			{
				m_output_path += "\\";
				m_output_path += detail::kStrings::DefaultXmlReportFileName;
			}
		}
	}
	/**
	 * @brief	�o�̓t�@�C���p�X�̎擾
	*/
	const ::std::string& GetFilePath(void) const { return m_output_path; }

public:
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

private:
	static void OnReportTestCase(IFile* file, const TestCase& test_case);
	static void OnReportTestInfo(IFile* file, const TestInfo& test_info);
	static void OnReportTestProperty(IFile* file, const TestResult& test_result
		, bool (*pfnValidate)(const ::std::string&));
	static void OnReportTestSkipped(IFile* file, const TestInfo& test_info);

private:
	bool FileOpen(const char* path);
	void FileClose(void);

private:
	static void	OutputXmlCDataSection(IFile* file, const char* data);
	static void OutputXmlAttribute(IFile* file, const char* name, const char* value);

private:
	static ::std::string EscapeXmlAttribute(const char* str)
	{
		return EscapeXml(str, true);
	}
	static ::std::string EscapeXmlText(const char* str)
	{
		return EscapeXml(str, false);
	}
	/**
	 * @brief	xml �Ŏg���Ȃ�������u������
	*/
	static ::std::string EscapeXml(const char* str, bool is_attribute);

	/**
	 * @brief	�󔒂��ǂ���
	 * @return	�^�U�l
	*/
	static IUTEST_CXX_CONSTEXPR bool IsWhitespace(char c)
	{
		return c == 0x9 || c == 0xA || c == 0xD;
	}
	/**
	 * @brief	xml �ɗ��p�\�ȕ������ǂ���
	 * @return	�^�U�l
	*/
	static IUTEST_CXX_CONSTEXPR bool IsValidXmlCharacter(char c)
	{
		return IsWhitespace(c) || c >= 0x20;
	}

public:
	/** @private */
	static void SetUp(void)
	{
		::std::string xmlpath = TestEnv::get_report_xml_filepath();
		if(!xmlpath.empty())
		{
			DefaultXmlGeneratorListener* listener = reinterpret_cast<DefaultXmlGeneratorListener*>(TestEnv::event_listeners().default_xml_generator());
			if(listener == NULL)
			{
				TestEnv::event_listeners().set_default_xml_generator(new DefaultXmlGeneratorListener(xmlpath));
				return;
			}
			listener->SetFilePath(xmlpath);
		}
	}
};

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_default_xml_generator.ipp"
#endif

#endif
