//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_random.hpp
 * @brief		iris unit test ���������� ��` �t�@�C��
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
#ifndef INCG_IRIS_iutest_random_HPP_89F260D7_9145_4b50_A8F0_B7A2696121B6_
#define INCG_IRIS_iutest_random_HPP_89F260D7_9145_4b50_A8F0_B7A2696121B6_

//======================================================================
// include
#include "iutest_time.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	����������N���X
*/
class iuRandom
{
	unsigned int m_v1, m_v2, m_v3, m_v4;
public:
	iuRandom(void)
	{
		init();
	}

	iuRandom(unsigned int seed)
	{
		init(seed);
	}

public:
	/**
	 * @brief	������
	 * @details	���ԂŃV�[�h������
	*/
	void	init(void)
	{
		init(GetIndefiniteValue());
	}
	/**
	 * @brief	������
	 * @param [in]	seed	= �V�[�h
	*/
	void	init(unsigned int seed)
	{
		m_v4 = seed;
		m_v3 = 1812433253 * ((m_v4 ^ (m_v4>>30)) + 1);
		m_v2 = 1812433253 * ((m_v3 ^ (m_v3>>30)) + 2);
		m_v1 = 1812433253 * ((m_v2 ^ (m_v2>>30)) + 3);
	}

public:
	/**
	 * @brief	�����̐���
	 * @return	����
	*/
	unsigned int		genrand(void)
	{
		const unsigned int t = (m_v1 ^ (m_v1<<11));
		m_v1 = m_v2;
		m_v2 = m_v3;
		m_v3 = m_v4;
		m_v4 = (m_v4 ^ (m_v4>>19)) ^ (t ^ (t>>8));
		return m_v4;
	}

	/**
	 * @brief	�����̐���
	 * @details	[0,max) �̗����𐶐�
	 * @param [in]	max	= ����l
	 * @return	����
	*/
	unsigned int		genrand(unsigned int max)
	{
		return genrand()%max;
	}

public:
	unsigned int operator ()(unsigned int max)
	{
		return genrand(max);
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
