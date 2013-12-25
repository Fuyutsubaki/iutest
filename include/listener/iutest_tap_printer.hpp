//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_tap_printer.hpp
 * @brief		iris unit test Test Anything Protocol �o�̓C�x���g���X�i�[ �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
#define INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	TAP�o�̓C�x���g���X�i�[
*/
class TAPPrintListener : public EmptyTestEventListener
{
public:
	TAPPrintListener(void) {}
public:
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

protected:
	/// �e�X�g�P�[�X���̏���
	void OnReportTestCase(detail::IOutStream* const stream, const TestCase& test_case, int top=1);

public:
	/**
	* @brief	TAPPrintListener �ɐ؂�ւ�
	*/
	static void SetUp(void)
	{
		TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
		delete listeners.Release(listeners.default_result_printer());
		listeners.Append(new TAPPrintListener);
	}
};

/**
 * @brief	TAP�t�@�C���o�̓C�x���g���X�i�[
*/
class TAPFileGeneratorListener : public TAPPrintListener
{
	::std::string	m_output_path;
public:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	directory = �o�̓f�B���N�g��
	*/
	TAPFileGeneratorListener(const char* directory=NULL)
	{
		SetFilePath(directory);
	}
public:
	/**
	 * @brief	�o�̓t�@�C���̐ݒ�
	*/
	void	SetFilePath(const char* directory)
	{
		if( directory == NULL || *directory == '\0' )
		{
			m_output_path = internal::posix::GetCWD();
		}
		else
		{
			m_output_path = directory;
			if( strchr(directory, '.') != NULL )
			{
				::std::string::size_type pos = m_output_path.rfind('\\');
				if( pos == ::std::string::npos )
				{
					m_output_path = internal::posix::GetCWD();
				}
				else
				{
					m_output_path = m_output_path.substr(0, pos);
				}
			}
		}
	}
public:
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE
	{
		IUTEST_UNUSED_VAR(test);
	}
	virtual void OnTestRecordProperty(const TestProperty& test_property) IUTEST_CXX_OVERRIDE
	{
		IUTEST_UNUSED_VAR(test_property);
	}
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

public:
	/**
	 * @brief	TAPFileGeneratorListener �ɐ؂�ւ�
	*/
	static void SetUp(void)
	{
		TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
		delete listeners.Release(listeners.default_result_printer());
		const ::std::string& output =  TestEnv::get_output_option();
		listeners.Append(new TAPFileGeneratorListener(output.c_str()));
	}
};

inline void TAPPrintListener::OnTestProgramStart(const UnitTest& test)
{
	IUTEST_UNUSED_VAR(test);
	// �t�B���^�����O
	if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
	{
		detail::iuConsole::color_output(detail::iuConsole::yellow, "# Note: iutest filter = %s\n", TestEnv::test_filter());
	}
}
inline void TAPPrintListener::OnTestProgramEnd(const UnitTest& test)
{
	detail::FileOutStream stream(stdout);

	int number = 1;
	for( int k=0, count=test.total_test_case_count(); k < count; ++k )
	{
		const TestCase& test_case = *test.GetTestCase(k);

		OnReportTestCase(&stream, test_case, number);

		number += test_case.total_test_count();
	}
	detail::iuConsole::output("1..%d\n", number-1);
}
inline void TAPPrintListener::OnReportTestCase(detail::IOutStream* const stream, const TestCase& test_case, int top)
{
	stream->Printf("# %s started.\n", test_case.name());

	for( int i=0, count=test_case.total_test_count(); i < count; ++i )
	{
		const TestInfo* test_info = test_case.GetTestInfo(i);
		if( !test_info->should_run() )
		{
			// �X�L�b�v
			stream->Printf("ok %d # SKIP - %s\n", top+i, test_info->name());
		}
		else
		{
			if( test_info->HasFailure() )
			{
				stream->Printf("not ok %d - %s ", top+i, test_info->name() );
				for( int j=0, count=test_info->result()->total_part_count(); j < count; ++j )
				{
					const TestPartResult& part = test_info->result()->GetTestPartResult(j);
					::std::string summary = part.make_message();
					// ���s��u������
					detail::StringReplace(summary, '\n', ", ");
					stream->Printf("%s. ", summary.c_str() );
				}
				stream->Printf("\n");
			}
			else
			{
				stream->Printf("ok %d - %s\n", top+i, test_info->name() );
			}
		}
	}

	stream->Printf("# %s ended.\n", test_case.name());
}

inline void TAPFileGeneratorListener::OnTestProgramEnd(const UnitTest& test)
{
	for( int k=0, count=test.total_test_case_count(); k < count; ++k )
	{
		const TestCase& test_case = *test.GetTestCase(k);

		IUTEST_UNUSED_VAR(test);
		IFile* fp = detail::IFileSystem::New();
		if( fp == NULL )
		{
			return;
		}

		::std::string filepath = m_output_path;
		::std::string name = test_case.name();
		detail::StringReplace(name, '/', "_");
		filepath += "\\";
		filepath += name;
		filepath += ".tap";

		if( !fp->Open(filepath.c_str(), IFile::OpenWrite) )
		{
			fprintf(stderr, "Unable to open file \"%s\".\n", filepath.c_str());
			fflush(stderr);
		}

		OnReportTestCase(fp, test_case);

		fp->Printf("1..%d\n", test_case.total_test_count());
	}
}

}	// end of namespace iutest

#endif	// INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
