//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_core.hpp
 * @brief		iris unit test core �t�@�C��
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
#ifndef INCG_IRIS_iutest_core_HPP_33560431_783B_4ae7_8FC8_6E78355CAF87_
#define INCG_IRIS_iutest_core_HPP_33560431_783B_4ae7_8FC8_6E78355CAF87_

//======================================================================
// include
#include "internal/iutest_result_reporter.hpp"
#include "internal/iutest_params_util.hpp"
#include "internal/iutest_file.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	�e�X�g�S�̂̊Ǘ���
*/
class UnitTest : public UnitTestImpl
{
public:
	/** @private */
	static	UnitTest&	instance(void)		{ static UnitTest inst; return inst; }
	/** 
	 * @brief	UnitTest �C���X�^���X�̎擾
	*/
	static	UnitTest*	GetInstance(void)	{ return &instance(); }

public:
	/**
	 * @brief	�e�X�g���� TestCase �̎擾
	*/
	const TestCase*		current_test_case(void)		const	{ return m_current_testcase; }

	/**
	 * @brief	�e�X�g���� TestInfo �̎擾
	 * @note	�݊����̂��� �����o�֐� �ɂ��Ă��܂��B
	*/
	const TestInfo*		current_test_info(void)		const	{ return Test::GetCurrentTestInfo(); }

	/** �����V�[�h�̎擾 */
	unsigned int		random_seed(void)			const	{ return TestEnv::current_random_seed(); }

	/** ���݉���ڂ̂���Ԃ����擾 */
	int					repeat_counter(void)		const	{ return m_repeat_counter; }

public:
	/** �e�X�g���� */
	int				total_test_count(void)		const	{ return m_total_test_num; }
	/** ���s����/����e�X�g���� */
	int				test_to_run_count(void)		const	{ return m_should_run_num; }
	/** ���s�e�X�g���� */
	int				failed_test_count(void)		const	{ return get_failed_test_count(); }
	/** �����e�X�g���� */
	int				disabled_test_count(void)	const	{ return m_disable_num; }
	/** �����e�X�g���� */
	int				successful_test_count(void)	const	{ return test_to_run_count() - failed_test_count() - test_was_skipped_count(); }
	/** �X�L�b�v�e�X�g���� */
	int				skip_test_count(void)		const	{ return total_test_count() - test_to_run_count() + test_was_skipped_count(); }
	/** �����I�ɃX�L�b�v���ꂽ�e�X�g���� */
	int				test_was_skipped_count(void) const	{ return get_skipped_test_count(); }

	/** �e�X�g�P�[�X���̑��� */
	int				total_test_case_count(void)	const	{ return m_testcases.size(); }
	/** ���s�����e�X�g�P�[�X���� */
	int				test_case_to_run_count(void)	const
	{
		int count=0;
		for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !(*it)->should_run() ) continue;
			++count;
		}
		return count;
	}
	/** ���������e�X�g�P�[�X���� */
	int				successful_test_case_count(void)	const
	{
		int count=0;
		for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !(*it)->should_run() ) continue;
			if( (*it)->failed_test_count() == 0 ) ++count;
		}
		return count;
	}
	/** ���s�����e�X�g�P�[�X���� */
	int				failed_test_case_count(void)	const
	{
		int count=0;
		for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !(*it)->should_run() ) continue;
			if( (*it)->failed_test_count() > 0 ) ++count;
		}
		return count;
	}

	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)		const	{ return m_elapsedmsec; }

	/** �e�X�g�P�[�X�̎擾 */
	const TestCase*	GetTestCase(int index)	const	{ return m_testcases[index]; }

	/** �e�X�g�������������ǂ��� */
	bool			Passed(void)			const	{ return get_failed_test_count() == 0 && m_ad_hoc_testresult.Passed(); }
	/** �e�X�g�����s�������ǂ��� */
	bool			Failed(void)			const	{ return !Passed(); }

	/** �C�x���g���X�i�[�̎擾 */
	TestEventListeners&	listeners(void)		const	{ return TestEnv::event_listeners(); }

protected:
	/**
	 * @brief	�e�X�g�̎��s
	*/
	int Run(void);

private:
#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
	int	RunOnMSC(void);
#endif
	int RunImpl(void);

	/**
	 * @brief	�e�X�g�̎��s�i�P���[�v�j
	*/
	bool	RunOnce(void);

private:
	/**
	 * @brief	�v���O�����̊J�n
	*/
	void	TestProgramStart(void);

	/**
	 * @brief	�C�e���[�V�������̃Z�b�g�A�b�v
	*/
	void	SetUpTestIteration(void);

	/**
	 * @brief	���Z�b�g�A�b�v
	*/
	void	EnvironmentSetUp(void);

	/**
	 * @brief	������
	*/
	void	EnvironmentTearDown(void);

	/**
	 * @brief	�v���O�����̏I��
	*/
	void	TestProgramEnd(void);

private:
	// C����̏I���R�[���o�b�N�֐�
	static void	OnExit(void)
	{
		instance().TestProgramEnd();
	}

private:
	UnitTest(void)
		: m_repeat_counter(0)
		, m_init_iutest_count(0)
		, m_current_testcase(NULL)
	{
		// �f�t�H���g���|�[�^�[���Z�b�g
		TestEnv::SetGlobalTestPartResultReporter(&m_default_test_part_result_reporter);
		// ���ϐ��ɂ��e�X�g�t���O�w������[�h
		TestEnv::LoadEnviromentVariable();
	}
	~UnitTest(void)
	{
		TestEnv::ReleaseGlobalTestEnvironment();
		TestEnv::SetGlobalTestPartResultReporter(NULL);
	}

private:
	// ����������
	void	Initialize(void);

	int get_failed_test_count(void) const
	{
		int count = 0;
		for( iuTestCases::const_iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !(*it)->should_run() ) continue;
			count += (*it)->failed_test_count();
		}
		return count;
	}

	int get_skipped_test_count(void) const
	{
		int count = 0;
		for( iuTestCases::const_iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			count += (*it)->test_was_skipped_count();
		}
		return count;
	}

#if IUTEST_HAS_PARAM_TEST
public:
	/** @private */
	ParamTestCaseHolder&	parameterized_test_registry(void)	{ return m_param_testcase_holder; }

private:
	ParamTestCaseHolder	m_param_testcase_holder;
#endif

private:
	friend class UnitTestSource;

	int m_repeat_counter;
	int m_init_iutest_count;
	const TestCase*	m_current_testcase;
	detail::DefaultGlobalTestPartResultReporter	m_default_test_part_result_reporter;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(UnitTest);
};

namespace detail
{

/**
 * @private
 * @internal
 * @brief	�P�̃e�X�g�C���X�^���X
*/
template<class Tester>
class TestInstance
{
public:
	// �R���X�g���N�^
	TestInstance(const char* testcase, const char* name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: m_mediator(AddTestCase(testcase, id, setup, teardown))
		, m_info(&m_mediator, name, &m_factory)
	{
		UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
	}
	// �R���X�g���N�^
	TestInstance(const char* testcase, const char* name, const char*  value_params, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: m_mediator(AddTestCase(testcase, id, setup, teardown))
		, m_info(&m_mediator, name, &m_factory)
	{
		m_info.set_value_param(value_params);
		UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
	}

private:
	TestCase* AddTestCase(const char* testcase, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
	{
		return UnitTest::instance().AddTestCase<TestCase>(testcase, id, setup, teardown);
	}
private:
	TestCaseMediator	m_mediator;
	TestInfo			m_info;
	iuFactory<Tester>	m_factory;
};

}	// end of namespace detail
}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_core.ipp"
#endif

#endif
