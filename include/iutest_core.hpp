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
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
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
	const TestCase*		current_test_case(void)	const	{ return m_current_testcase; }

	/**
	 * @brief	�e�X�g���� TestInfo �̎擾
	 * @note	�݊����̂��� �����o�֐� �ɂ��Ă��܂��B
	*/
	const TestInfo*		current_test_info(void)	const	{ return Test::GetCurrentTestInfo(); }

	/** �����V�[�h�̎擾 */
	unsigned int		random_seed(void)		const	{ return TestEnv::current_random_seed(); }

	/** ���݉���ڂ̂���Ԃ����擾 */
	int					repeat_counter(void)	const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_repeat_counter; }

public:
	/** �e�X�g���� */
	int				total_test_count(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_total_test_num; }
	/** ���|�[�g�Ώۂ̃e�X�g���� */
	int				reportable_test_count(void)	const;
	/** ���s����/����e�X�g���� */
	int				test_to_run_count(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_should_run_num; }
	/** ���s�e�X�g���� */
	int				failed_test_count(void)		const;
	/** �����e�X�g���� */
	int				disabled_test_count(void)	const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_disable_num; }
	/** ���|�[�g�Ώۂ̖����e�X�g���� */
	int				reportable_disabled_test_count(void) const;
	/** �����e�X�g���� */
	int				successful_test_count(void)	const;
	/** �X�L�b�v�e�X�g���� */
	int				skip_test_count(void)		const;
	/** ���|�[�g�Ώۂ̃X�L�b�v�e�X�g���� */
	int				reportable_skip_test_count(void) const;
	/** �����I�ɃX�L�b�v���ꂽ�e�X�g���� */
	int				test_run_skipped_count(void) const;
	/** ���|�[�g�Ώۂ̖����I�ɃX�L�b�v���ꂽ�e�X�g���� */
	int				reportable_test_run_skipped_count(void) const;

	/** �e�X�g�P�[�X���̑��� */
	int				total_test_case_count(void)	const	{ return m_testcases.size(); }
	/** ���s�����e�X�g�P�[�X���� */
	int				test_case_to_run_count(void) const;
	/** ���������e�X�g�P�[�X���� */
	int				successful_test_case_count(void) const;
	/** ���s�����e�X�g�P�[�X���� */
	int				failed_test_case_count(void) const;

	/** �e�X�g���s������Ȃ��Ƃ��̃��U���g�̎擾 */
	const TestResult* ad_hoc_testresult(void) const IUTEST_CXX_NOEXCEPT_SPEC { return &m_ad_hoc_testresult; }

	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_elapsedmsec; }

	/** �e�X�g�J�n���̃^�C���X�^���v���擾 */
	TimeInMillisec	start_timestamp(void)	const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_start_timestamp; }

	/** �e�X�g�P�[�X�̎擾 */
	const TestCase*	GetTestCase(int index)	const	{ return m_testcases[index]; }

	/** �e�X�g�������������ǂ��� */
	bool			Passed(void)			const;
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
		, m_test_started(false)
		, m_start_timestamp(0)
	{
		// �f�t�H���g���|�[�^�[���Z�b�g
		TestEnv::SetGlobalTestPartResultReporter(&m_default_test_part_result_reporter);
		// ���ϐ��ɂ��e�X�g�t���O�w������[�h
		TestEnv::LoadEnviromentVariable();
	}
#if defined(_MSC_VER) && _MSC_VER < 1300
public:	// VC++6.0 bug
#endif
	~UnitTest(void)
	{
		TestEnv::ReleaseGlobalTestEnvironment();
		TestEnv::SetGlobalTestPartResultReporter(NULL);
	}

private:
	// ����������
	void	Initialize(void);

#if IUTEST_HAS_PARAM_TEST
public:
	/** @private */
	ParamTestCaseHolder&	parameterized_test_registry(void) IUTEST_CXX_NOEXCEPT_SPEC { return m_param_testcase_holder; }

private:
	ParamTestCaseHolder	m_param_testcase_holder;
#endif

private:
	friend class UnitTestSource;

	int m_repeat_counter;
	int m_init_iutest_count;
	bool m_test_started;
	TimeInMillisec m_start_timestamp;
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
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
		return UnitTest::instance().AddTestCase<TestCase>(testcase, id, setup, teardown);
#else
		return UnitTest::instance().AddTestCase(testcase, id, setup, teardown, &detail::type<TestCase>());
#endif
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
