//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_case.hpp
 * @brief		iris unit test testcase �t�@�C��
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
#ifndef INCG_IRIS_IUTEST_CASE_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_IUTEST_CASE_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "iutest_info.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	�e�X�g�P�[�X
*/
class TestCase
	: public detail::iu_list_node<TestCase>
{
protected:
	typedef detail::iu_list<TestInfo>	iuTestInfos;	//!< TestInfo ���X�g
	//typedef ::std::vector<TestInfo*>	iuTestInfos;	//!< TestInfo ���X�g
protected:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase_name	= �e�X�g�P�[�X��
	 * @param [in]	id				= �e�X�g�P�[�XID
	 * @param [in]	setup			= �e�X�g���O���s�֐�
	 * @param [in]	teardown		= �e�X�g������s�֐�
	*/
	TestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
	: m_testcase_name(testcase_name)
	, m_setup(setup), m_teardown(teardown)
	, m_id(id), m_disable_num(0)
	, m_should_run_num(0)
	, m_elapsedmsec(0)
	, m_disable(false)
	{
		if( detail::IsStringForwardMatching(testcase_name, "DISABLED_") )
		{
			m_disable = true;
		}
	}

public:
	/**
	 * @brief	�f�X�g���N�^
	*/
	virtual	~TestCase(void) {}

public:
	/** test case ���̎擾 */
	const	char*	name(void)					const	{ return m_testcase_name.c_str(); }

	/** �e�X�g���� */
	int				total_test_count(void)		const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_testinfos.size(); }
	/** ���|�[�g�Ώۂ̃e�X�g���� */
	int				reportable_test_count(void)	const;
	/** ���s�����e�X�g���� */
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
	/** �e�X�g�̎��s�~���b */
	TimeInMillisec	elapsed_time(void)			const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_elapsedmsec; }

	/** TestInfo �̎擾 */
	const TestInfo*	GetTestInfo(int index)		const	{ return m_testinfos[index]; }
	/** should_run */
	bool			should_run(void)			const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_should_run_num != 0; }

	/** �e�X�g�������������ǂ��� */
	bool			Passed(void)				const	{ return failed_test_count() == 0 && m_ad_hoc_testresult.Passed(); }
	/** �e�X�g�����s�������ǂ��� */
	bool			Failed(void)				const	{ return !Passed(); }

	/** type param ������̎擾 */
	virtual const char*	type_param(void)		const	{ return NULL; }

	/** TestCase �o�͏��̎擾 */
	::std::string testcase_name_with_where(void) const
	{
		::std::string str = m_testcase_name;
		if( type_param() != NULL )
		{
			str += ", where TypeParam = ";
			str += type_param();
		}
		return str;
	}

	/** �e�X�g���s������Ȃ��Ƃ��̃��U���g�̎擾 */
	const TestResult* ad_hoc_testresult(void) const IUTEST_CXX_NOEXCEPT_SPEC { return &m_ad_hoc_testresult; }

public:
	/**
	 * @brief	�L���ȃv���p�e�B�����ǂ����`�F�b�N
	 * @param [in] name	= �v���p�e�B��
	 * @retval	true=�L��
	 * @retval	false=����
	*/
	static bool ValidateTestPropertyName(const ::std::string& name)
	{
		const char* ban[] = { "name", "tests", "failures", "disabled", "skip", "errors", "time" };
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
		return TestProperty::ValidateName(name, ban);
#else
		return TestProperty::ValidateName(name, ban, ban+IUTEST_PP_COUNTOF(ban));
#endif
	}

private:
	/**
	 * @brief	�e�X�g�̎��s
	 * @return	����
	*/
	bool	Run(void);

	/**
	 * @brief	���s
	 * @return	����
	*/
	bool	RunImpl(void);

public:
	/**
	 * @private
	 * @brief	�e�X�g�P�[�X��r�p�I�u�W�F�N�g
	*/
	struct FindOp
	{
		TestTypeId	m_id;
		const char*	m_name;

		bool operator () (const TestCase* p) const
		{
			if( p->get_typeid() == m_id && (strcmp(p->name(), m_name) == 0) )
			{
				return true;
			}
			return false;
		}
	};
private:
	/**
	 * @brief	�e�X�g�̃N���A
	*/
	void	clear(void);
	/*
	 * @brief	�e�X�g�̃t�B���^�����O
	 * @return	���s����ꍇ�͐^
	*/
	bool	filter(void);

private:
	friend bool	operator == (const TestCase& lhs, const TestCase& rhs)
	{
		return (lhs.m_id == rhs.m_id) && (strcmp(lhs.name(), rhs.name()) == 0);
	}

	void	push_back(TestInfo* p)	{ m_testinfos.push_back(p); }

private:
	iuTestInfos::const_iterator	begin(void)	const		{ return m_testinfos.begin(); }
	iuTestInfos::const_iterator	end(void)	const		{ return m_testinfos.end(); }
	TestTypeId					get_typeid(void) const IUTEST_CXX_NOEXCEPT_SPEC	{ return m_id; }

private:
	static bool IsSuccessfulTest(const TestInfo* p) { return p->is_ran() && p->Passed(); }
	static bool IsFaildTest(const TestInfo* p) { return p->should_run() && p->HasFailure(); }
	static bool IsSkipTest(const TestInfo* p) { return !p->is_ran() || p->is_skipped(); }
	static bool IsReportableSkipTest(const TestInfo* p) { return p->is_reportable() && IsSkipTest(p); }
	static bool IsRunSkippedTest(const TestInfo* p) { return p->should_run() && p->is_skipped(); }
	static bool IsReportableRunSkippedTest(const TestInfo* p) { return p->is_reportable() && IsRunSkippedTest(p); }
	static bool IsReportableDisabledTest(const TestInfo* p) { return p->is_reportable() && p->is_disabled_test(); }

private:
	friend class UnitTestImpl;
	friend class UnitTest;

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
	friend struct FindOp;
#endif

	::std::string	m_testcase_name;	//!< �e�X�g�P�[�X��
	iuTestInfos		m_testinfos;		//!< �e�X�g��񃊃X�g
	SetUpMethod		m_setup;			//!< SetUp �֐�
	TearDownMethod	m_teardown;			//!< TearDown �֐�
	TestTypeId		m_id;				//!< TypeID
	int				m_disable_num;		//!< ���������e�X�g�̑���
	int				m_should_run_num;	//!< ���s���ׂ��e�X�g�̑���
	TimeInMillisec	m_elapsedmsec;		//!< �e�X�g����
	bool			m_disable;			//!< �����^�U�l
	TestResult		m_ad_hoc_testresult;	//!< �e�X�g�����s���łȂ��Ƃ��̃��U���g

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestCase);
};

/**
 * @brief	�^���e�X�g�P�[�X
*/
template<typename T>
class TypedTestCase : public TestCase
{
public:
	typedef T	TypeParam;	//!< �^

protected:
	/**
	 * @brief	�R���X�g���N�^
	 * @param [in]	testcase_name	= �e�X�g�P�[�X��
	 * @param [in]	id				= �e�X�g�P�[�XID
	 * @param [in]	setup			= �e�X�g���O���s�֐�
	 * @param [in]	teardown		= �e�X�g������s�֐�
	*/
	TypedTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: TestCase(testcase_name, id, setup, teardown)
		, m_type_param(detail::GetTypeName<TypeParam>())
	{}

public:
	/** type param ������̎擾 */
	virtual const char*	type_param(void) const IUTEST_CXX_OVERRIDE	{ return m_type_param.empty() ? NULL : m_type_param.c_str(); }

private:
	friend class UnitTestImpl;

	::std::string	m_type_param;		//!< type param string
};

namespace detail
{

/**
 * @brief	�e�X�g�P�[�X�����
*/
class TestCaseMediator : public detail::iuITestCaseMediator
{
public:
	TestCaseMediator(TestCase* p) IUTEST_CXX_NOEXCEPT_SPEC : iuITestCaseMediator(p) {}
public:
	virtual const char*	test_case_name(void) const IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL { return m_test_case->name(); }
	virtual const char*	type_param(void)	 const IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL { return m_test_case->type_param(); }
};

}	// end of namespace detail
}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_case.ipp"
#endif

#endif
