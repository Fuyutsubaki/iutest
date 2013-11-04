//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_body.hpp
 * @brief		iris unit test �e�X�g�P�̃N���X �t�@�C��
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
#ifndef INCG_IRIS_iutest_body_HPP_3EEA6706_9954_4330_B292_129667FA6B96_
#define INCG_IRIS_iutest_body_HPP_3EEA6706_9954_4330_B292_129667FA6B96_

//======================================================================
// include
#include "iutest_result.hpp"
#include "iutest_printers.hpp"
#include "internal/iutest_mediator.hpp"

namespace iutest
{

//======================================================================
// declare
class Test;
template<typename T>class WithParamInterface;
template<typename T>class TestWithParam;

//======================================================================
// class
/**
 * @brief	�e�X�g�x�[�X
*/
class Test
{
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(Test);

public:
	Test(void)
		: test_info_(NULL)
		, m_test_info(NULL)
		, m_random_seed(0)
	{
		CurrentTestObserver::s_current = this;
	}

	virtual ~Test(void)
	{
		CurrentTestObserver::s_current = NULL;
	}

public:
	/**
	 * @brief	���s���� TestInfo �̎擾
	*/
	static const TestInfo*	GetCurrentTestInfo(void)
	{
		const Test* curr = GetCurrentTest();
		if( curr == NULL || curr->m_test_info == NULL ) return NULL;
		return curr->m_test_info->ptr();
	}

	/**
	 * @brief	���s���� Test �̎擾
	*/
	static Test*			GetCurrentTest(void) { return CurrentTestObserver::GetCurrentTest(); }


	/**
	 * @brief	�v���I�ȃG���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasFatalFailure(void)
	{
		return GetCurrentTest()->m_test_info->HasFatalFailure();
	}

	/**
	 * @brief	�v���I�ł͂Ȃ��G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasNonfatalFailure(void)
	{
		return GetCurrentTest()->m_test_info->HasNonfatalFailure();
	}

	/**
	 * @brief	�G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasFailure(void)
	{
		return GetCurrentTest()->m_test_info->HasFailure();
	}

	/**
	 * @brief	�e�X�g���ʂ̏��ǉ�
	 * @param [in]	key		= �v���p�e�B�̃L�[
	 * @param [in]	value	= �l
	*/
	static void RecordProperty(const ::std::string& key, const ::std::string& value);

	/**
	 * @brief	�e�X�g���ʂ̏��ǉ�
	 * @param [in]	key		= �v���p�e�B�̃L�[
	 * @param [in]	value	= �l
	*/
	template<typename T>
	static void RecordProperty(const ::std::string& key, const T& value)
	{
		RecordProperty(key, PrintToString(value));
	}

#if IUTEST_HAS_GENRAND

	/**
	 * @brief	�����̐���
	 * @note	�����V�[�h�� --iutest_random_seed �Ŏw�肵���l�ɂȂ�܂��B
	 *			�w�肵�Ȃ������ꍇ�͎��s���Ɍ��肵�܂��B
	*/
	unsigned int	genrand(void)				{ return m_random.genrand(); }
	/**
	 * @overload
	 * @param [in]	max	= ����l
	 * @return		[0,max) �̗����𐶐�
	*/
	unsigned int	genrand(unsigned int max)	{ return m_random.genrand(max); }
	/**
	 * @overload
	 * @return		max	= [0,1] �̗����𐶐�
	*/
	float			genrandf(void)				{ return m_random.genrandf(); }
	/** �����V�[�h�̎擾 */
	unsigned int	random_seed(void) const IUTEST_CXX_NOEXCEPT_SPEC { return m_random_seed; }

	/** ����������̎擾 */
	detail::iuRandom& random_engine(void)		{ return m_random; }

#endif

protected:
	virtual	void	SetUp(void)		{}	//!< ���s�O����
	virtual void	Body(void)	= 0;	//!< �e�X�g������
	virtual void	TearDown(void)	{}	//!< ���s�㏈��

public:
	static	void	SetUpTestCase(void)		{}	//!< test case setup
	static	void	TearDownTestCase(void)	{}	//!< test case tear down

private:
	/**
	 * @brief	�e�X�g�̎��s
	*/
	void Run(detail::iuITestInfoMediator* test_info);

private:
	template<typename DMY>
	class Observer
	{
	public:
		static Test* s_current;
	public:
		static Test* GetCurrentTest(void) IUTEST_CXX_NOEXCEPT_SPEC { return s_current; }
	};

	typedef Observer<void>	CurrentTestObserver;

private:
	class TestRecordPropertyHelper
	{
	public:
		static 	void RecordProperty(const TestProperty& prop);
	};
protected:
	const TestInfo* test_info_;	//!< �e�X�g���ɊȒP�ɃA�N�Z�X�\�Ȃ悤��

private:
	friend class UnitTest;
	friend class UnitTestImpl;
	friend class TestInfo;

	detail::iuITestInfoMediator*	m_test_info;
#if IUTEST_HAS_GENRAND
	detail::iuRandom				m_random;
	unsigned int					m_random_seed;
#endif
};

/**
 * @brief	�p�����[�^�e�X�g�C���^�[�t�F�[�X
 * @tparam	T = �p�����[�^�^
*/
template<typename T>
class WithParamInterface
{
public:
	typedef T	ParamType;	//!< �p�����[�^�^
protected:
	virtual ~WithParamInterface(void)	{}

public:
	/**
	 * @brief	�p�����[�^�̎擾
	*/
	static const ParamType&	GetParam(void)
	{
		IUTEST_CHECK_(s_params != NULL) << "GetParam() can only use the value-parameterized test";
#if defined(_MSC_VER) && _MSC_VER >= 1500
		__analysis_assume(s_params != NULL);
#endif
		return *s_params;
	}

	/** @private */
	static void SetParam(const ParamType* params) IUTEST_CXX_NOEXCEPT_SPEC { s_params = params; }

private:
	static const ParamType*	s_params;
};

template<typename T>
const T* WithParamInterface<T>::s_params = NULL;

/**
 * @brief	�p�����[�^�e�X�g�x�[�X
 * @tparam	T = �p�����[�^�^
*/
template<typename T>
class TestWithParam : public Test, public WithParamInterface<T>
{
};

}	// end of namespace iutest

template<typename DMY>
::iutest::Test*	::iutest::Test::Observer<DMY>::s_current = NULL;

#if !IUTEST_HAS_LIB
#  include "impl/iutest_body.ipp"
#endif

#endif
