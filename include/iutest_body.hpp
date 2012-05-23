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
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
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
	static const TestInfo*	GetCurrentTestInfo(void)		{ return CurrentTestObserver::GetCurrentTestInfo(); }

	/**
	 * @brief	���s���� Test �̎擾
	*/
	static Test*			GetCurrentTest(void)			{ return CurrentTestObserver::GetCurrentTest(); }


	/**
	 * @brief	�v���I�ȃG���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasFatalFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasFatalFailure();
	}

	/**
	 * @brief	�v���I�ł͂Ȃ��G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasNonfatalFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasNonfatalFailure();
	}

	/**
	 * @brief	�G���[���o�����ǂ���
	 * @return	�^�U�l
	*/
	static bool	HasFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasFailure();
	}

	/**
	 * @brief	�e�X�g���ʂ̏��ǉ�
	 * @param [in]	key		= �v���p�e�B�̃L�[
	 * @param [in]	value	= �l
	*/
	static void RecordProperty(const char* key, const char* value)
	{
		// �s���ȃL�[�̃`�F�b�N
		const char* ban[] = { "name", "status", "time", "classname", "type_param", "value_param" };
		std::string key_ = key;
		for( int i=0, n=sizeof(ban)/sizeof(ban[0]); i < n; ++i )
		{
			if( key_ == ban[i] )
			{
				key_ += "_";
				break;
			}
		}
		TestProperty prop(key_.c_str(), value);
		GetCurrentTest()->m_test_info->RecordProperty(prop);
		TestEnv::event_listeners().OnTestRecordProperty(prop);
	};
	/**
	 * @brief	�e�X�g���ʂ̏��ǉ�
	 * @param [in]	key		= �v���p�e�B�̃L�[
	 * @param [in]	value	= �l
	*/
	template<typename T>
	static void RecordProperty(const char* key, const T& value)
	{
		RecordProperty(key, PrintToString(value).c_str());
	}

#if IUTEST_HAS_GENRAND

	/**
	 * @brief	�����̐���
	 * @note	�����V�[�h�� --iutest_random_seed �Ŏw�肵���l�ɂȂ�܂��B
	 *			�w�肵�Ȃ������ꍇ�͎��s���Ɍ��肵�܂��B
	*/
	unsigned int	genrand(void)				{ return m_random.genrand(); }
	/** @ref genrand */
	unsigned int	genrand(unsigned int max)	{ return m_random.genrand(max); }

#endif

protected:
	virtual	void	SetUp(void)		{}	//!< ���s�O����
	virtual void	Body(void)	= 0;	//!< �e�X�g������
	virtual void	TearDown(void)	{}	//!< ���s�㏈��

public:
	static	void	SetUpTestCase(void)		{}	//!< test case setup
	static	void	TearDownTestCase(void)	{}	//!< test case tear down

protected:
	/**
	 * @brief	�e�X�g�̎��s
	*/
	void Run(detail::iuITestInfoMediator* test_info)
	{
		m_test_info = test_info;
		test_info_ = test_info->ptr();
		if( TestEnv::get_random_seed() == 0 )
		{
			m_random.init();
		}
		else
		{
			m_random.init(TestEnv::get_random_seed());
		}

		SetUp();
		Body();
		TearDown();

		test_info_ = NULL;
		m_test_info = NULL;
	}

private:
	template<typename DMY=void>
	class Observer
	{
	public:
		static Test*	s_current;
	public:
		static		 Test*		GetCurrentTest(void)		{ return s_current; }
		static const TestInfo*	GetCurrentTestInfo(void)	{ if( s_current == NULL ) return NULL; return s_current->m_test_info->ptr(); }
	};

	typedef Observer<void>	CurrentTestObserver;

protected:
	const TestInfo* test_info_;	//!< �e�X�g���ɊȒP�ɃA�N�Z�X�\�Ȃ悤��

private:
	friend class UnitTest;
	friend class UnitTestImpl;
	friend class TestInfo;

	detail::iuITestInfoMediator*	m_test_info;
#if IUTEST_HAS_GENRAND
	detail::iuRandom				m_random;
#endif
};

template<typename DMY>
Test*	Test::Observer<DMY>::s_current = NULL;

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
	static const ParamType&	GetParam(void)						{ return *s_params; }

	/** @private */
	static void				SetParam(const ParamType* params)	{ s_params = params; }

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

#endif
