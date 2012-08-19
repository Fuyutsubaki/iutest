//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_env.hpp
 * @brief		iris unit test �� �t�@�C��
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
#ifndef INCG_IRIS_iutest_env_HPP_F4017EAB_6CA3_4e6e_8983_059393DADD04_
#define INCG_IRIS_iutest_env_HPP_F4017EAB_6CA3_4e6e_8983_059393DADD04_

//======================================================================
// include
#include "internal/iutest_charcode.hpp"
#include "internal/iutest_random.hpp"
#include "internal/iutest_regex.hpp"
#include "iutest_listener.hpp"

//======================================================================
// define
/**
 * @ingroup	IUTEST_UTIL
 * @brief	�t���O�Z�b�g
 * @details	�w��\�ȃt���O\n
 *			shuffle (bool)\n
 *			also_run_disabled_tests (bool)\n
 *			break_on_failure (bool)\n
 *			throw_on_failure (bool)\n
 *			catch_exceptions (bool)\n
 *			random_seed (unsigned int)\n
 *			print_time (bool)\n
 *          color (string)\n
 *          filter (string)\n
 *          repeat (int)\n
 *			list_tests (bool)\n
*/
#define IUTEST_FLAG(name)	IIUT_FLAG(name)

/**
 * @private
 * @{
*/
#define IIUT_FLAG(name)		TestEnv::name()

/**
 * @}
*/

namespace iutest
{

//======================================================================
// function
/**
 * @brief	���ϐ��̎擾
*/
inline ::std::string EnvironmentString(const char* name) { ::std::string var; detail::GetEnvironmentVariable(name, var); return var; }

//======================================================================
// class
/**
 * @brief	���Z�b�g�N���X
*/
class Environment
{
public:
	virtual ~Environment(void)	{}
	virtual void SetUp(void)	{}	//!< ���O����
	virtual void TearDown(void)	{}	//!< ���㏈��
};

/**
 * @brief	�e�X�g�t���O
*/
class TestFlag
{
public:
	/**
	 * @brief	�e�X�g�t���O�ۑ�/�����N���X
	*/
	class ScopedGuard
	{
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(ScopedGuard);

		int m_test_flags;
	public:
		ScopedGuard(void) 
		{
			m_test_flags = TestFlag::GetInstance().m_test_flags;
		}
		~ScopedGuard(void) 
		{
			TestFlag::GetInstance().m_test_flags = m_test_flags;
		}
	};
public:
	/** 
	 * @brief	�t���O
	*/
	enum Kind
	{
		SHUFFLE_TESTS			= 0x00000001,	//!< �V���b�t���e�X�g
		RUN_DISABLED_TESTS		= 0x00000002,	//!< DISABLED �e�X�g�����s
		FILTERING_TESTS			= 0x00000004,	//!< �e�X�g�̃t�B���^�����O
		BREAK_ON_FAILURE		= 0x00000010,	//!< �e�X�g���s���Ƀu���[�N
		THROW_ON_FAILURE		= 0x00000040,	//!< �v���I�Ȏ��s���� throw ����
		CONSOLE_COLOR_ON		= 0x00000100,	//!< �F���o��ON
		CONSOLE_COLOR_OFF		= 0x00000200,	//!< �F���o��OFF
		CONSOLE_COLOR_ANSI		= 0x00000400,	//!< �G�X�P�[�v�V�[�P���X�ŏo��
		PRINT_TIME				= 0x00001000,	//!< �o�ߎ��Ԃ̏o��
		CATCH_EXCEPTION_EACH	= 0x00010000,	//!< ��O�� catch ����(TestInfo)
		CATCH_EXCEPTION_GLOBAL	= 0x00020000,	//!< ��O�� catch ����(UnitTest)
		CATCH_EXCEPTION			= 0x00030000,	//!< ��O�� catch ����
		OUTPUT_XML_REPORT		= 0x01000000,	//!< xml �o��
		SHOW_HELP				= 0x10000000,	//!< �w���v�\��
		SHOW_VERSION			= 0x20000000,	//!< �o�[�W�����\��
		SHOW_TESTS_LIST			= 0x40000000,	//!< �e�X�g�̃��X�g�\��
		SHOW_FEATURE			= 0x80000000,	//!< �@�\�̏o��
		MASK					= 0xFFFFFFFF,	//!< �}�X�N

		DEFAULT = CATCH_EXCEPTION|PRINT_TIME		//!< �f�t�H���g
	};

private:
	TestFlag(void)
		: m_test_flags(DEFAULT) {}

public:
	/** @private */
	static TestFlag&	GetInstance(void)	{ static TestFlag flag; return flag; }
public:
	/**
	 * @brief	�t���O�̃r�b�g����
	 * @details	flag = (flag | enable) & mask;
	 * @param [in]	enable	= �_���a
	 * @param [in]	mask	= �}�X�N�l
	*/
	static void		SetFlag(int enable, int mask=-1)	{ GetInstance().m_test_flags |= enable; GetInstance().m_test_flags &= mask; }
	/**
	 * @brief	�t���O�������Ă��邩�ǂ���
	 * @param [in]	flag	= �����Ώۃt���O
	 * @return	�^�U�l
	*/
	static bool		IsEnableFlag(int flag)				{ return GetInstance().m_test_flags & flag ? true : false; }

private:
	template<int KIND>
	class Fragment
	{
		typedef Fragment<KIND>	_Myt;
	public:
		Fragment(void) {}
		Fragment(bool f)	{ SetFlag(KIND, f ? -1 : ~KIND); }
		_Myt&	operator = (bool f)	{ SetFlag(KIND, f ? -1 : ~KIND); return *this; }
		operator bool (void) const { return IsEnableFlag(KIND); }
	};

private:
	friend	class TestEnv;

	int m_test_flags;
};

// declare
class TestPartResultReporterInterface;

/**
 * @brief	�e�X�g��
*/
class TestEnv
{
	typedef ::std::vector<Environment*>	iuEnvironmentList;
private:
	class OptionString
	{
	protected:
		::std::string	m_option;
	public:
		bool operator == (const char* c_str_)		{ return m_option == c_str_; }
		bool operator == (const ::std::string& str)	{ return m_option == str; }
		bool operator != (const char* c_str_)		{ return m_option != c_str_; }
		bool operator != (const ::std::string& str)	{ return m_option != str; }

	public:
		const char* c_str(void) const	{ return m_option.c_str(); }
		size_t	length(void) const		{ return m_option.length(); }
	};

public:

	/**
	 * @private
	 * @{
	*/
	typedef TestFlag::Fragment<TestFlag::SHUFFLE_TESTS>			shuffle;
	typedef TestFlag::Fragment<TestFlag::RUN_DISABLED_TESTS>	also_run_disabled_tests;
	typedef TestFlag::Fragment<TestFlag::BREAK_ON_FAILURE>		break_on_failure;
	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION>		catch_exceptions;
	typedef TestFlag::Fragment<TestFlag::THROW_ON_FAILURE>		throw_on_failure;
	typedef TestFlag::Fragment<TestFlag::PRINT_TIME>			print_time;
	typedef TestFlag::Fragment<TestFlag::SHOW_TESTS_LIST>		list_tests;

	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_EACH>		catch_exceptions_each;
	typedef TestFlag::Fragment<TestFlag::CATCH_EXCEPTION_GLOBAL>	catch_exceptions_global;

	/**
	 * @}
	*/

	/**
	 * @private
	 * @brief	�����V�[�h�ݒ�p�I�u�W�F�N�g
	*/
	typedef class RandomSeedSet
	{
	public:
		RandomSeedSet(void) {}
		RandomSeedSet(unsigned int seed) { init_random(seed); } 
		RandomSeedSet&	operator = (unsigned int seed)	{ init_random(seed); return *this; }
		operator unsigned int (void) const { return get_random_seed(); }
	} random_seed;

	/**
	 * @private
	 * @brief	���s�[�g�񐔐ݒ�p�I�u�W�F�N�g
	*/
	typedef class RepeatCountSet
	{
	public:
		RepeatCountSet(void) {}
		RepeatCountSet(int count) { set_repeat_count(count); } 
		RepeatCountSet&	operator = (int count)	{ set_repeat_count(count); return *this; }
		operator int (void) const { return get_repeat_count(); }
	} repeat;

	/**
	 * @private
	 * @brief	�F�t���o�̓I�v�V�����ݒ�p�I�u�W�F�N�g
	*/
	typedef class ColorOptionSet : public OptionString
	{
	public:
		ColorOptionSet(void)
		{
			if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_OFF) ) m_option = "no";
			else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ON) ) m_option = "yes";
			else if( TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ANSI) ) m_option = "ansi";
			else m_option = "auto";
		}
		const ColorOptionSet& operator = (const char* c_str_)
		{
			m_option = c_str_;
			ParseOutputOption(c_str_);
			return *this;
		}
		const ColorOptionSet& operator = (const ::std::string& str)
		{
			m_option = str;
			ParseOutputOption(str.c_str());
			return *this;
		}
	} color;

	/**
	 * @private
	 * @brief	�t�B���^�[�I�v�V�����ݒ�p�I�u�W�F�N�g
	*/
	typedef class FilterOption : public OptionString
	{
	public:
		FilterOption(void)
		{
			m_option = get_vars().m_test_filter;
		}
		const FilterOption& operator = (const char* c_str_)
		{
			m_option = c_str_;
			set_test_filter(c_str_);
			return *this;
		}
		const FilterOption& operator = (const ::std::string& str)
		{
			m_option = str;
			set_test_filter(str.c_str());
			return *this;
		}
	} filter;

private:
	struct Variable
	{
		Variable(void)
			: m_random_seed(0)
			, m_current_random_seed(0)
			, m_repeat_count(1)
			, m_testpartresult_reporter(NULL)
		{}
		unsigned int		m_random_seed;
		unsigned int		m_current_random_seed;
		int					m_repeat_count;
		::std::string		m_report_file;
		::std::string		m_test_filter;
		detail::iuRandom	m_genrand;
		iuEnvironmentList	m_environment_list;
		TestEventListeners	m_event_listeners;
		TestPartResultReporterInterface*	m_testpartresult_reporter;
	};

	static Variable& get_vars(void) { static Variable v; return v; }

public:

	static detail::iuRandom&	genrand(void)				{ return get_vars().m_genrand; }				//!< ����������
	static unsigned int			get_random_seed(void)		{ return get_vars().m_random_seed; }			//!< �����V�[�h
	static unsigned int			current_random_seed(void)	{ return get_vars().m_current_random_seed; }	//!< �����V�[�h
	static int					get_repeat_count(void)		{ return get_vars().m_repeat_count; }			//!< �J��Ԃ���
	static const char*			get_report_filepath(void)	{ return get_vars().m_report_file.c_str(); }	//!< �o��xml�p�X
	static const char*			test_filter(void)			{ return get_vars().m_test_filter.c_str(); }	//!< �t�B���^�[������

	/** @private */
	static TestEventListeners&	event_listeners(void)	{ return get_vars().m_event_listeners; }
	/** @private */
	static TestPartResultReporterInterface* GetGlobalTestPartResultReporter(void)		{ return get_vars().m_testpartresult_reporter; }
	/** @private */
	static void SetGlobalTestPartResultReporter(TestPartResultReporterInterface* ptr)	{ get_vars().m_testpartresult_reporter = ptr; }

private:
	static iuEnvironmentList&	environments(void)		{ return get_vars().m_environment_list; }

public:
	/**
	 * @brief	�O���[�o�����Z�b�g�N���X�̒ǉ�
	 * @param [in]	env	= ���Z�b�g�N���X�A�h���X
	 * @return	�o�^���ꂽ�N���X�A�h���X
	*/
	static Environment* AddGlobalTestEnvironment(Environment* env)
	{
		if( env == NULL ) return NULL;
		environments().push_back(env);
		return env;
	}

private:
	/**
	 * @brief	���Z�b�g�N���X�̉��
	*/
	static void ReleaseGlobalTestEnvironment(void)
	{
		// ���ׂĉ������
		for( iuEnvironmentList::iterator it=environments().begin(); it != environments().end(); )
		{
			Environment* p = *it;
			it = environments().erase(it);
			delete p;
		}
	}

public:
	/**
	 * @private
	 * @brief	�R�}���h���C�������̉��
	*/
	template<typename CharType>
	static void	ParseCommandLine(int* pargc, CharType** argv)
	{
		int argc = *pargc;

		for( int i=0; i < argc; )
		{
			if( ParseCommandLineElem(argv[i]) )
			{
				--argc;
				// ���������ꍇ�A�I�v�V�����𖖔��Ɉړ�
				for( int k=i; k < argc; ++k )
				{
					CharType* tmp = argv[k];
					argv[k] = argv[k+1];
					argv[k+1] = tmp;
				}
			}
			else
			{
				++i;
			}
		}
		*pargc = argc;
	}

	/**
	 * @private
	 * @brief	�R�}���h���C�������̉��(vector)
	*/
	template<typename CharType>
	static void	ParseCommandLine(::std::vector< ::std::basic_string<CharType> >& argv)
	{
		for( typename ::std::vector< ::std::basic_string<CharType> >::iterator it = argv.begin(); it != argv.end(); )
		{
			if( ParseCommandLineElem(it->c_str()) )
			{
				it = argv.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
private:
	template<typename CharType>
	static bool	ParseCommandLineElem(CharType* argv)
	{
		typedef typename detail::mbs_ptr<CharType>::type formatter;

		bool find = false;
		formatter argv_format;
		const char* str = argv_format.ptr(argv);
		if( *str == '-' )
		{
			find = true;
			++str;
			if( *str == '-' )
			{
				++str;
				bool iuoption = false;
				{
					const char* const base_str = str;
					if( *str == 'g' ) 
					{
						++str;
						iuoption = true;
					}
					if(*str == 'i' && *(str+1) == 'u' )
					{
						str += 2;
						iuoption = true;
					}
					const char option_prefix[] = "test_";
					for( int i=0, size=sizeof(option_prefix)/sizeof(option_prefix[0])-1; i < size; ++i, ++str )
					{
						if( *str != option_prefix[i] )
						{
							iuoption = false;
							str = base_str;
							break;
						}
					}
				}
				if( iuoption )
				{
					// --iutest_*
					if( strstr(str, "output") == str )
					{
						find = ParseOutputOption(ParseOptionSettingStr(str));
					}
					else if( detail::IsStringEqual(str, "list_tests") )
					{
						TestFlag::SetFlag(TestFlag::SHOW_TESTS_LIST);
					}
					else if( strstr(str, "color") == str )
					{
						find = ParseColorOption(ParseOptionSettingStr(str));
					}
					else if( detail::IsStringEqual(str, "shuffle") )
					{
						TestFlag::SetFlag(TestFlag::SHUFFLE_TESTS);
					}
					else if( strstr(str, "random_seed") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							char* end = NULL;
							long seed = strtol(opt, &end, 0);
							init_random(static_cast<unsigned int>(seed));
						}
						else
						{
							find = false;
						}
					}
					else if( detail::IsStringEqual(str, "also_run_disabled_tests") )
					{
						TestFlag::SetFlag(TestFlag::RUN_DISABLED_TESTS);
					}
					else if( strstr(str, "break_on_failure") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::BREAK_ON_FAILURE, 1);
					}
					else if( strstr(str, "catch_exceptions") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::CATCH_EXCEPTION, -1);
					}
					else if( strstr(str, "throw_on_failure") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::THROW_ON_FAILURE, 1);
					}
					else if( strstr(str, "print_time") == str )
					{
						find = ParseYesNoFlagOption(str, TestFlag::PRINT_TIME, -1);
					}
					else if( strstr(str, "repeat") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							char* end = NULL;
							long count = strtol(opt, &end, 0);
							set_repeat_count(static_cast<int>(count));
						}
						else
						{
							find = false;
						}
					}
					else if( strstr(str, "filter") == str )
					{
						const char* opt = ParseOptionSettingStr(str);
						if( opt != NULL )
						{
							set_test_filter(opt);
						}
					}
					else
					{
						find = false;
					}
					if( !find )
					{
						// �Y������I�v�V�������Ȃ��ꍇ�̓w���v�\��
						TestFlag::SetFlag(TestFlag::SHOW_HELP);
					}
				}
				else if( detail::IsStringEqual(str, "help") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_HELP);
				}
				else if( detail::IsStringEqual(str, "version") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_VERSION);
				}
				else if( detail::IsStringEqual(str, "feature") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_FEATURE);
				}
				else
				{
					find = false;
				}
			}
			else
			{
				if( detail::IsStringEqual(str, "v") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_VERSION);
				}
				else if( detail::IsStringEqual(str, "h")
					|| detail::IsStringEqual(str, "?") )
				{
					TestFlag::SetFlag(TestFlag::SHOW_HELP);
				}
				else
				{
					find = false;
				}
			}
		}
		return find;
	}

private:
	/**
	 * @brief	���ϐ�����ݒ�\�z
	*/
	static void LoadEnviromentVariable(void)
	{
		{
			int var = 0;
			if( detail::GetEnvironmentInt("IUTEST_ALSO_RUN_DISABLED_TESTS", var) )
			{
				TestFlag::SetFlag(TestFlag::RUN_DISABLED_TESTS
					, var ? TestFlag::MASK : ~(TestFlag::RUN_DISABLED_TESTS) );
			}
			if( detail::GetEnvironmentInt("IUTEST_SHUFFLE", var) )
			{
				TestFlag::SetFlag(TestFlag::SHUFFLE_TESTS
					, var ? TestFlag::MASK : ~(TestFlag::SHUFFLE_TESTS) );
			}
			if( detail::GetEnvironmentInt("IUTEST_RANDOM_SEED", var) )
			{
				init_random((unsigned int)var);
			}
			if( detail::GetEnvironmentInt("IUTEST_CATCH_EXCEPTIONS", var) )
			{
				TestFlag::SetFlag(TestFlag::CATCH_EXCEPTION
					, var ? TestFlag::MASK : ~(TestFlag::CATCH_EXCEPTION) );
			}
			if( detail::GetEnvironmentInt("IUTEST_BREAK_ON_FAILURE", var) )
			{
				TestFlag::SetFlag(TestFlag::BREAK_ON_FAILURE
					, var ? TestFlag::MASK : ~(TestFlag::BREAK_ON_FAILURE) );
			}
			if( detail::GetEnvironmentInt("IUTEST_THROW_ON_FAILURE", var) )
			{
				TestFlag::SetFlag(TestFlag::THROW_ON_FAILURE
					, var ? TestFlag::MASK : ~(TestFlag::THROW_ON_FAILURE) );
			}
			if( detail::GetEnvironmentInt("IUTEST_PRINT_TIME", var) )
			{
				TestFlag::SetFlag(TestFlag::PRINT_TIME
					, var ? TestFlag::MASK : ~(TestFlag::PRINT_TIME) );
			}
			if( detail::GetEnvironmentInt("IUTEST_REPEAT", var) )
			{
				set_repeat_count(var);
			}
		}
		{
			char var[128] = {0};
			if( detail::GetEnvironmentVariable("IUTEST_COLOR", var) )
			{
				ParseColorOption(var);
			}
		}
		{
			char path[260+32] = {0};
			if( detail::GetEnvironmentVariable("IUTEST_OUTPUT", path) )
			{
				ParseOutputOption(path);
			}
			if( detail::GetEnvironmentVariable("IUTEST_FILTER", path) )
			{
				set_test_filter(path);
			}
		}
	}

private:
	/**
	 * @brief	�Z�b�g�A�b�v
	*/
	static void	SetUp(void)
	{
		unsigned int seed = get_random_seed();
		if( seed == 0 )
		{
			seed = detail::GetIndefiniteValue();
		}
		get_vars().m_current_random_seed = seed;
		genrand().init(seed);
	}

private:
	/**
	 * @brief	�����V�[�h�̐ݒ�
	*/
	static void	init_random(unsigned int seed)
	{
		get_vars().m_random_seed = seed;
	}

	/**
	 * @brief	�J��Ԃ��񐔂̐ݒ�
	*/
	static void	set_repeat_count(int count)
	{
		get_vars().m_repeat_count = count;
	}

	/**
	 * @brief	�t�B���^�[������̐ݒ�
	*/
	static void	set_test_filter(const char* str)
	{
		get_vars().m_test_filter = str;
		TestFlag::SetFlag(TestFlag::FILTERING_TESTS);
	}

private:
	/**
	 * @brief	�I�v�V���������񂩂�ݒ蕶����̐擪�A�h���X���擾
	*/
	static inline const char* ParseOptionSettingStr(const char* opt)
	{
		const char* eq = strchr(opt, '=');
		if( eq == NULL ) return eq;
		return eq+1;
	}
	/**
	 * @brief	IUTEST_COLOR �I�v�V�����̔���
	*/
	static bool	ParseColorOption(const char* option)
	{
		if( option == NULL ) return false;

		if( IsYes(option) )
		{
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON, ~TestFlag::CONSOLE_COLOR_OFF);
		}
		else if( IsNo(option) )
		{
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_OFF, ~TestFlag::CONSOLE_COLOR_ON);
		}
		else if( detail::IsStringCaseEqual(option, "auto") )
		{
			// auto
			TestFlag::SetFlag(0, ~(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_OFF));
		}
		else if( detail::IsStringCaseEqual(option, "ansi") )
		{
			// ansi
			TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_ANSI, ~TestFlag::CONSOLE_COLOR_OFF);
		}
		else 
		{
			return false;
		}
		return true;
	}

	/**
	 * @brief	IUTEST_OUTPUT �I�v�V�����̔���
	*/
	static bool	ParseOutputOption(const char* option)
	{
		if( option == NULL ) return false;
		if( strstr(option, "xml") != NULL )
		{
			TestFlag::SetFlag(TestFlag::OUTPUT_XML_REPORT);
		}
		else
		{
			return false;
		}
		const char* file = strchr(option+3, ':');
		if( file != NULL )
		{
			get_vars().m_report_file = file+1;
		}
		return true;
	}

	/**
	 * @brief	yes �I�v�V������ no �I�v�V�������̔���
	 * @param [in]	option	= �I�v�V����������
	 * @param [in]	flag	= �t���O
	 * @param [in]	def		= �����Ȃ��̏ꍇ�̃I�y���[�V����
	 * @return	����
	*/
	static bool ParseYesNoFlagOption(const char* option, TestFlag::Kind flag, int def)
	{
		const char* str = ParseOptionSettingStr(option);
		int yesno = str != NULL ? ParseYesNoOption(str) : def;
		if( yesno < 0 )
		{
			return false;
		}
		TestFlag::SetFlag(flag, yesno ? TestFlag::MASK : ~(flag) );
		return true;
	}

	/**
	 * @brief	yes �I�v�V������ no �I�v�V�������̔���
	 * @param [in]	option	= �I�v�V����������
	 * @retval	< 0	= �Y���Ȃ�
	 * @retval	0	= NO
	 * @retval	> 0 = YES
	*/
	static int ParseYesNoOption(const char* option)
	{
		if( option == NULL ) return -1;
		if( IsYes(option) ) return 1;
		if( IsNo(option) ) return 0;
		return -1;
	}

	/**
	 * @brief	yes �I�v�V����������
	*/
	static bool IsYes(const char* option)
	{
		if( detail::IsStringCaseEqual(option, "yes")
			|| detail::IsStringCaseEqual(option, "y")
			|| detail::IsStringCaseEqual(option, "on")
			|| detail::IsStringCaseEqual(option, "true")
			|| detail::IsStringCaseEqual(option, "t")
			|| detail::IsStringEqual(option, "1") ) 
		{
			return true;
		}
		return false;
	}
	/**
	 * @brief	no �I�v�V����������
	*/
	static bool IsNo(const char* option)
	{
		if( detail::IsStringCaseEqual(option, "no")
			|| detail::IsStringCaseEqual(option, "n")
			|| detail::IsStringCaseEqual(option, "off")
			|| detail::IsStringCaseEqual(option, "false")
			|| detail::IsStringCaseEqual(option, "f")
			|| detail::IsStringEqual(option, "0") ) 
		{
			return true;
		}
		return false;
	}

private:
	friend class UnitTest;
};

}	// end of namespace iutest

#endif
