//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_case.ipp
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
#ifndef INCG_IRIS_IUTEST_CASE_IPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_IUTEST_CASE_IPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "../iutest_case.hpp"

namespace iutest
{

IUTEST_IPP_INLINE bool	TestCase::Run(void)
{
	if( !should_run() ) return true;

	if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
	{
		detail::RandomShuffle(m_testinfos, TestEnv::genrand());
	}

	// �e�X�g�J�n
	TestEnv::event_listeners().OnTestCaseStart(*this);
	const bool result = RunImpl();
	// �e�X�g�I��
	TestEnv::event_listeners().OnTestCaseEnd(*this);

	return result;
}

IUTEST_IPP_INLINE bool TestCase::RunImpl(void)
{
	bool result=true;
	m_elapsedmsec = 0;

	m_setup();

	if( m_ad_hoc_testresult.HasFatalFailure() )
	{
		return false;
	}

	{
		detail::iuStopWatch sw;
		sw.start();
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( (it)->should_run() )
			{
				// ���s
				if( !(it)->Run() )
				{
					result = false;
				}
			}
		}
		m_elapsedmsec = sw.stop();
	}
	m_teardown();
	return result;
}

IUTEST_IPP_INLINE void	TestCase::clear(void)
{
	m_ad_hoc_testresult.Clear();
	for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		(it)->clear();
	}
}

IUTEST_IPP_INLINE bool	TestCase::filter(void)
{
	m_should_run_num = 0;
	m_disable_num = 0;
	for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		if( m_disable )
		{
			// DISABLE �̓`��
			(it)->m_disable = true;
		}
		if( (it)->is_disabled_test() )
		{
			++m_disable_num;
		}
		if( (it)->filter() )
		{
			++m_should_run_num;
		}
	}
	return should_run();
}

IUTEST_IPP_INLINE int TestCase::reportable_test_count(void) const
{
	return detail::CountIfOverList(m_testinfos, &TestInfo::is_reportable);
}

IUTEST_IPP_INLINE int TestCase::failed_test_count(void) const
{
	if( !should_run() ) return 0;
	//if( m_ad_hoc_testresult.Failed() ) return m_testinfos.count();
	return detail::CountIf(m_testinfos, IsFaildTest);
}

IUTEST_IPP_INLINE int TestCase::successful_test_count(void) const
{
	if( !should_run() ) return 0;
	//if( m_ad_hoc_testresult.Failed() ) return 0;
	return detail::CountIf(m_testinfos, IsSuccessfulTest);
}

IUTEST_IPP_INLINE int TestCase::skip_test_count(void) const
{
	if( !should_run() ) return total_test_count();
	return detail::CountIf(m_testinfos, IsSkipTest);
}

IUTEST_IPP_INLINE int TestCase::reportable_skip_test_count(void) const
{
	if( !should_run() ) return reportable_test_count();
	return detail::CountIf(m_testinfos, IsReportableSkipTest);
}

IUTEST_IPP_INLINE int TestCase::test_run_skipped_count(void) const
{
	if( !should_run() ) return 0;
	return detail::CountIf(m_testinfos, IsRunSkippedTest);
}

IUTEST_IPP_INLINE int TestCase::reportable_test_run_skipped_count(void) const
{
	if( !should_run() ) return 0;
	return detail::CountIf(m_testinfos, IsReportableRunSkippedTest);
}

IUTEST_IPP_INLINE int TestCase::reportable_disabled_test_count(void) const
{
	return detail::CountIf(m_testinfos, IsReportableDisabledTest);
}

}	// end of namespace iutest

#endif
