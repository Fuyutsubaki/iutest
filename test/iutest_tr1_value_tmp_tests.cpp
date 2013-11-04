//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_tr1_value_tmp_tests.cpp
 * @brief		������
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

//======================================================================
// include
#include "../include/iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

#include "../include/tr1/iutest_value_tmp_tests.hpp"

#if IUTEST_HAS_TYPED_TEST

/**
 * @note	���̂悤�ȃe�X�g���������ꍇ�A�^�t�� �������� �^���p�����[�^�������e�X�g�ŁA
 *			�v�f�̌^�ɁA�K�v�Ȍ^�E�l�̒�`������Ώ\���ł���
*/

template<int N>
class factorial
{
	template<int M, typename DMY>
	struct impl
	{
		static const int value = M * factorial<M-1>::value;
	};
	template<typename DMY>
	struct impl<1, DMY>
	{
		static const int value = 1;
	};
	template<typename DMY>
	struct impl<0, DMY>
	{
		static const int value = 0;
	};
	// �����͏ȗ�
public:
	static const int value = impl<N, void>::value;
};

template<int N>
class TestValueType : public ::iutest::Test
{
protected:
	static const int V = factorial<N>::value;
};

typedef ::iutest::Types< ::iutest::TemplateValue<10>, ::iutest::TemplateValue<0> > Types;

IUTEST_VALUETMP_TEST_CASE(TestValueType, Types);

IUTEST_VALUETMP_TEST(TestValueType, Equal)
{
	IUTEST_SUCCEED() << this->V;
}

template<typename T>
class TestValueType2 : public ::iutest::Test
{
};

IUTEST_TYPED_TEST_CASE(TestValueType2, Types);

IUTEST_TYPED_TEST(TestValueType2, Equal)
{
	IUTEST_SUCCEED() << factorial<TypeParam::kValue>::value;
}

#endif

#endif

