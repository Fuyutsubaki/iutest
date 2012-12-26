//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_listener.hpp
 * @brief		iris unit test �C�x���g���X�i�[ ��` �t�@�C��
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
#ifndef INCG_IRIS_iutest_listener_HPP_C94B8142_F8B3_413f_B479_8AA2B78604CE_
#define INCG_IRIS_iutest_listener_HPP_C94B8142_F8B3_413f_B479_8AA2B78604CE_

//======================================================================
// include
#include <vector>
#include <algorithm>

namespace iutest
{

//======================================================================
// declare
class UnitTest;
class TestInfo;
class TestCase;
class TestPartResult;
class TestProperty;

namespace detail
{
	class DefaultGlobalTestPartResultReporter;
}

/**
 * @brief	�C�x���g���X�i�[
*/
class TestEventListener
{
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestEventListener);
public:
	TestEventListener(void) {}
	virtual ~TestEventListener(void)	{}
public:
	virtual void OnTestProgramStart(const UnitTest& test)			= 0;	//!< �e�X�g�v���O�����J�n���ɌĂ΂�܂�
	virtual void OnTestIterationStart(const UnitTest& test
									, int iteration)				= 0;	//!< �P�̃e�X�g�J�n���ɖ���Ă΂�܂�
	virtual void OnEnvironmentsSetUpStart(const UnitTest& test)		= 0;	//!< �O���[�o�����ݒ� SetUp �O�ɌĂ΂�܂�
	virtual void OnEnvironmentsSetUpEnd(const UnitTest& test)		= 0;	//!< �O���[�o�����ݒ� SetUp ��ɌĂ΂�܂�
	virtual void OnTestCaseStart(const TestCase& test_case)			= 0;	//!< �e�X�g�P�[�X�J�n���ɌĂ΂�܂�
	virtual void OnTestStart(const TestInfo& test_info)				= 0;	//!< �e�X�g�J�n���ɌĂ΂�܂�
	virtual void OnTestPartResult(const TestPartResult& test_part_result)	= 0;	//!< �e�X�g���s���ɌĂ΂�܂�
	virtual void OnTestRecordProperty(const TestProperty& /*test_property*/) {}	//!< RecordProperty ���ɌĂ΂�܂�
	virtual void OnTestEnd(const TestInfo& test_info)				= 0;	//!< �e�X�g�P�[�X�I�����ɂɌĂ΂�܂�
	virtual void OnTestCaseEnd(const TestCase& test_case)			= 0;	//!< �e�X�g�I�����ɂɌĂ΂�܂�
	virtual void OnEnvironmentsTearDownStart(const UnitTest& test)	= 0;	//!< �O���[�o�����ݒ� TearDown �O�ɌĂ΂�܂�
	virtual void OnEnvironmentsTearDownEnd(const UnitTest& test)	= 0;	//!< �O���[�o�����ݒ� TearDown �O�ɌĂ΂�܂�
	virtual void OnTestIterationEnd(const UnitTest& test
									, int iteration)				= 0;	//!< �P�̃e�X�g�I�����ɖ���Ă΂�܂�
	virtual void OnTestProgramEnd(const UnitTest& test)				= 0;	//!< �e�X�g�v���O�����I�����ɌĂ΂�܂�
};

/**
 * @brief	��̃C�x���g���X�i�[
*/
class EmptyTestEventListener : public TestEventListener
{
public:
	virtual void OnTestProgramStart(const UnitTest& /*test*/)			IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestIterationStart(const UnitTest& /*test*/
									, int /*iteration*/)				IUTEST_CXX_OVERRIDE	{}
	virtual void OnEnvironmentsSetUpStart(const UnitTest& /*test*/)		IUTEST_CXX_OVERRIDE	{}
	virtual void OnEnvironmentsSetUpEnd(const UnitTest& /*test*/)		IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestCaseStart(const TestCase& /*test_case*/)			IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestStart(const TestInfo& /*test_info*/)				IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestPartResult(const TestPartResult& /*test_part_result*/) IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestRecordProperty(const TestProperty& /*test_propterty*/) IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestEnd(const TestInfo& /*test_info*/)				IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestCaseEnd(const TestCase& /*test_case*/)			IUTEST_CXX_OVERRIDE	{}
	virtual void OnEnvironmentsTearDownStart(const UnitTest& /*test*/)	IUTEST_CXX_OVERRIDE	{}
	virtual void OnEnvironmentsTearDownEnd(const UnitTest& /*test*/)	IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestIterationEnd(const UnitTest& /*test*/
									, int /*iteration*/)				IUTEST_CXX_OVERRIDE	{}
	virtual void OnTestProgramEnd(const UnitTest& /*test*/)				IUTEST_CXX_OVERRIDE	{}
};

/**
 * @brief	�C�x���g���s�C�x���g���X�i�[
*/
class TestEventRepeater : public TestEventListener
{
	typedef ::std::vector<TestEventListener*>	ListenerContainer;
public:
	/**
	 * @brief	���X�i�[�̒ǉ�
	*/
	void	Append(TestEventListener* listener)
	{
		m_listeners.push_back(listener);
	};

	/**
	 * @brief	���X�i�[�̉��
	*/
	TestEventListener*	Release(TestEventListener* listener);

public:
	// On*End �͌�납����s
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestIterationStart(const UnitTest& test
									, int iteration) IUTEST_CXX_OVERRIDE;
	virtual void OnEnvironmentsSetUpStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnEnvironmentsSetUpEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestCaseStart(const TestCase& test_case) IUTEST_CXX_OVERRIDE;
	virtual void OnTestStart(const TestInfo& test_info) IUTEST_CXX_OVERRIDE;
	virtual void OnTestPartResult(const TestPartResult& test_part_result) IUTEST_CXX_OVERRIDE;
	virtual void OnTestRecordProperty(const TestProperty& test_property) IUTEST_CXX_OVERRIDE;
	virtual void OnTestEnd(const TestInfo& test_info) IUTEST_CXX_OVERRIDE;
	virtual void OnTestCaseEnd(const TestCase& test_case) IUTEST_CXX_OVERRIDE;
	virtual void OnEnvironmentsTearDownStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnEnvironmentsTearDownEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestIterationEnd(const UnitTest& test
									, int iteration) IUTEST_CXX_OVERRIDE;
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

private:
	ListenerContainer	m_listeners;
};

/**
 * @brief	�C�x���g���X�i�[�̊Ǘ��N���X
*/
class TestEventListeners
{
	typedef ::std::vector<TestEventListener*>	ListenerContainer;

public:
	TestEventListeners(void) : m_default_result_printer(NULL), m_default_xml_generator(NULL) {}

public:
	/**
	 * @brief	���X�i�[�̒ǉ�
	*/
	void	Append(TestEventListener* listener)	{ m_repeater.Append(listener); };

	/**
	 * @brief	���X�i�[�̉��
	*/
	TestEventListener*	Release(TestEventListener* listener) { return m_repeater.Release(listener); }

public:
	/**
	 * @brief	�f�t�H���g�o�̓��X�i�[�̎擾
	*/
	TestEventListener*	default_result_printer(void)	const	{ return m_default_result_printer; }
	/**
	 * @brief	�f�t�H���gxml�o�̓��X�i�[�擾
	*/
	TestEventListener*	default_xml_generator(void)		const	{ return m_default_xml_generator; }

private:
	TestEventListener*	repeater(void) { return &m_repeater; }

	void OnTestProgramStart(const UnitTest& test)					{ m_repeater.OnTestProgramStart(test); }
	void OnTestIterationStart(const UnitTest& test, int iteration)	{ m_repeater.OnTestIterationStart(test, iteration); }
	void OnEnvironmentsSetUpStart(const UnitTest& test)				{ m_repeater.OnEnvironmentsSetUpStart(test); }
	void OnEnvironmentsSetUpEnd(const UnitTest& test)				{ m_repeater.OnEnvironmentsSetUpEnd(test); }

	void OnTestCaseStart(const TestCase& test_case)					{ m_repeater.OnTestCaseStart(test_case); }
	void OnTestStart(const TestInfo& test_info)						{ m_repeater.OnTestStart(test_info); }
	void OnTestPartResult(const TestPartResult& test_part_result)	{ m_repeater.OnTestPartResult(test_part_result); }
	void OnTestRecordProperty(const TestProperty& test_property)	{ m_repeater.OnTestRecordProperty(test_property); }
	void OnTestEnd(const TestInfo& test_info)						{ m_repeater.OnTestEnd(test_info); }
	void OnTestCaseEnd(const TestCase& test_case)					{ m_repeater.OnTestCaseEnd(test_case); }

	void OnEnvironmentsTearDownStart(const UnitTest& test)			{ m_repeater.OnEnvironmentsTearDownStart(test); }
	void OnEnvironmentsTearDownEnd(const UnitTest& test)			{ m_repeater.OnEnvironmentsTearDownEnd(test); }
	void OnTestIterationEnd(const UnitTest& test, int iteration)	{ m_repeater.OnTestIterationEnd(test, iteration); }
	void OnTestProgramEnd(const UnitTest& test)						{ m_repeater.OnTestProgramEnd(test); }

private:
	void	set_default_result_printer(TestEventListener* listener);
	void	set_default_xml_generator(TestEventListener* listener);

private:
	friend class UnitTestSource;
	friend class UnitTest;
	friend class TestInfo;
	friend class TestCase;
	friend class Test;

	friend class detail::DefaultGlobalTestPartResultReporter;
	friend class DefaultXmlGeneratorListener;
	friend class DefalutResultPrintListener;

	TestEventRepeater	m_repeater;
	TestEventListener*	m_default_result_printer;
	TestEventListener*	m_default_xml_generator;
};

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_listener.ipp"
#endif

#endif
