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
	virtual void OnTestProgramStart(const UnitTest& /*test*/)			{}
	virtual void OnTestIterationStart(const UnitTest& /*test*/
									, int /*iteration*/)				{}
	virtual void OnEnvironmentsSetUpStart(const UnitTest& /*test*/)		{}
	virtual void OnEnvironmentsSetUpEnd(const UnitTest& /*test*/)		{}
	virtual void OnTestCaseStart(const TestCase& /*test_case*/)			{}
	virtual void OnTestStart(const TestInfo& /*test_info*/)				{}
	virtual void OnTestPartResult(const TestPartResult& /*test_part_result*/)	{}
	virtual void OnTestRecordProperty(const TestProperty& /*test_propterty*/)	{}
	virtual void OnTestEnd(const TestInfo& /*test_info*/)				{}
	virtual void OnTestCaseEnd(const TestCase& /*test_case*/)			{}
	virtual void OnEnvironmentsTearDownStart(const UnitTest& /*test*/)	{}
	virtual void OnEnvironmentsTearDownEnd(const UnitTest& /*test*/)	{}
	virtual void OnTestIterationEnd(const UnitTest& /*test*/
									, int /*iteration*/)				{}
	virtual void OnTestProgramEnd(const UnitTest& /*test*/)				{}
};

/**
 * @brief	�C�x���g���X�i�[�̊Ǘ��N���X
*/
class TestEventListeners
{
	typedef std::vector<TestEventListener*>	ListenerContainer;

public:
	TestEventListeners(void) : m_default_result_printer(NULL), m_default_xml_generator(NULL) {}

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
	TestEventListener*	Release(TestEventListener* listener)
	{
		ListenerContainer::iterator it = std::find(m_listeners.begin(), m_listeners.end(), listener);
		if( it == m_listeners.end() ) return NULL;
		m_listeners.erase(it);
		return listener;
	}

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
	// On*End �͌�납����s

	void OnTestProgramStart(const UnitTest& test)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestProgramStart(test);
		}
	}
	void OnTestIterationStart(const UnitTest& test, int iteration)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestIterationStart(test, iteration);
		}
	}
	void OnEnvironmentsSetUpStart(const UnitTest& test)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnEnvironmentsSetUpStart(test);
		}
	}
	void OnEnvironmentsSetUpEnd(const UnitTest& test)
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnEnvironmentsSetUpEnd(test);
		}
	}

	void OnTestCaseStart(const TestCase& test_case)	
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestCaseStart(test_case);
		}
	}
	void OnTestStart(const TestInfo& test_info)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestStart(test_info);
		}
	}
	void OnTestPartResult(const TestPartResult& test_part_result)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestPartResult(test_part_result);
		}
	}
	void OnTestRecordProperty(const TestProperty& test_property)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnTestRecordProperty(test_property);
		}
	}
	void OnTestEnd(const TestInfo& test_info)
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnTestEnd(test_info);
		}
	}
	void OnTestCaseEnd(const TestCase& test_case)	
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnTestCaseEnd(test_case);
		}
	}

	void OnEnvironmentsTearDownStart(const UnitTest& test)
	{
		for( ListenerContainer::iterator it=m_listeners.begin(), end=m_listeners.end(); it != end; ++it )
		{
			(*it)->OnEnvironmentsTearDownStart(test);
		}
	}
	void OnEnvironmentsTearDownEnd(const UnitTest& test)
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnEnvironmentsTearDownEnd(test);
		}
	}
	void OnTestIterationEnd(const UnitTest& test, int iteration)
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnTestIterationEnd(test, iteration);
		}
	}
	void OnTestProgramEnd(const UnitTest& test)
	{
		for( ListenerContainer::reverse_iterator it=m_listeners.rbegin(), end=m_listeners.rend(); it != end; ++it )
		{
			(*it)->OnTestProgramEnd(test);
		}
	}

private:
	void	set_default_result_printer(TestEventListener* listener)
	{
		Release(m_default_result_printer);
		if( listener != NULL )
		{
			m_listeners.push_back(listener);
		}
		m_default_result_printer = listener;
	}
	void	set_default_xml_generator(TestEventListener* listener)
	{
		Release(m_default_xml_generator);
		if( listener != NULL )
		{
			m_listeners.push_back(listener);
		}
		m_default_xml_generator = listener;
	}
private:
	friend class UnitTestSource;
	friend class UnitTest;
	friend class TestInfo;
	friend class TestCase;
	friend class Test;

	friend class detail::DefaultGlobalTestPartResultReporter;
	friend class DefaultXmlGeneratorListener;
	friend class DefalutResultPrintListener;

	ListenerContainer	m_listeners;
	TestEventListener*	m_default_result_printer;
	TestEventListener*	m_default_xml_generator;
};

}	// end of namespace iutest

#endif
