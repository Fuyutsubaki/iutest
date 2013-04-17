//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_body.ipp
 * @brief		iris unit test �e�X�g�P�̃N���X �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_body_IPP_3EEA6706_9954_4330_B292_129667FA6B96_
#define INCG_IRIS_iutest_body_IPP_3EEA6706_9954_4330_B292_129667FA6B96_

//======================================================================
// include
#include "../iutest_body.hpp"

namespace iutest
{

IUTEST_IPP_INLINE void Test::RecordProperty(const ::std::string& key, const ::std::string& value)
{
	TestProperty prop(key, value);
	TestRecordPropertyHelper::RecordProperty(prop);
}

IUTEST_IPP_INLINE 	void Test::Run(detail::iuITestInfoMediator* test_info)
{
	m_test_info = test_info;
	test_info_ = test_info->ptr();
	unsigned int seed = TestEnv::get_random_seed();
	if( seed == 0 )
	{
		seed = detail::GetIndefiniteValue();
	}
	m_random_seed = seed;
	m_random.init(seed);

	SetUp();

	if( !HasFailure() )
	{
		Body();
	}

	TearDown();

	test_info_ = NULL;
	m_test_info = NULL;
}

}	// end of namespace iutest

#endif
