//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_filepath.hpp
 * @brief		iris unit test �t�@�C���p�X�N���X �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_filepath_HPP_D69E7545_BF8A_4edc_9493_9105C69F9378_
#define INCG_IRIS_iutest_filepath_HPP_D69E7545_BF8A_4edc_9493_9105C69F9378_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include "iutest_string.hpp"
#include "iutest_port.hpp"

#if IUTEST_HAS_FILE_STAT
#  include <sys/stat.h>
#endif

#if	defined(_MSC_VER) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <direct.h>
#endif

namespace iutest {

namespace internal {
namespace posix
{

#if IUTEST_HAS_FILE_STAT

#if defined(IUTEST_OS_WINDOWS)

	typedef struct _stat StatStruct;

	inline int Stat(const char* path, StatStruct* buf) { return _stat(path, buf); }
	inline bool IsDir(const StatStruct& st) { return (st.st_mode & _S_IFDIR) != 0; }

#else

	typedef struct stat StatStruct;

	inline int Stat(const char* path, StatStruct* buf) { return stat(path, buf); }
	inline bool IsDir(const StatStruct& st) { return S_ISDIR(st.st_mode); }

#endif

#endif


	IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}	// end of namespace posix
}	// end of namespace internal

namespace detail
{

//======================================================================
// class
/**
 * @brief	�t�@�C���p�X�N���X
*/
class iuFilePath
{
public:
	iuFilePath(void) : m_path("") {}
	iuFilePath(const iuFilePath& rhs) : m_path(rhs.m_path) {}

	explicit iuFilePath(const char* path) : m_path(path)
	{
		Normalize();
	}
	explicit iuFilePath(const std::string& path) : m_path(path)
	{
		Normalize();
	}

public:
	std::string	ToString(void)	const	{ return m_path; }
	const char* c_str(void)		const	{ return m_path.c_str(); }
	bool		IsEmpty(void)	const	{ return c_str() == NULL || *c_str() == '\0'; }
	size_t		length(void)	const	{ return m_path.length(); }

public:
	bool operator == (const iuFilePath& rhs) const
	{
		return IsStringCaseEqual(c_str(), rhs.c_str());
	}
	bool operator == (const char* rhs) const
	{
		return IsStringCaseEqual(c_str(), rhs);
	}
	//operator const char* (void) const	{ return c_str(); }

public:

	/**
	 * @brief	�t�H���_�p�X���ǂ���
	*/
	bool	IsDirectory(void) const
	{
		return !m_path.empty() &&
			IsPathSeparator(m_path.c_str()[length()-1]);
	}

	/**
	 * @brief	���[�g�f�B���N�g���p�X���ǂ���
	*/
	bool	IsRootDirectory(void) const
	{
#ifdef IUTEST_OS_WINDOWS
		if( length() != 3 ) return false;
#else
		if( length() != 3 ) return false;
#endif
		return IsAbsolutePath();
	}

	/**
	 * @brief	��΃p�X���ǂ���
	*/
	bool	IsAbsolutePath(void) const
	{
#ifdef IUTEST_OS_WINDOWS
		if( length() < 3 ) return false;
		const char* name = m_path.c_str();

		if( IsDBCSLeadByte(name[0]) )
		{
			++name;
		}
		return (name[1] == ':' && IsPathSeparator(name[0]));
#else
		return IsPathSeparator(m_path.c_str()[0]);
#endif
	}

	/**
	 * @brief	�����̃Z�p���[�^�[���폜
	*/
	iuFilePath	RemoveTrailingPathSeparator(void) const
	{
		return IsDirectory() ? iuFilePath(std::string(m_path.c_str(), length()-1)) : *this;
	}

	/**
	 * @brief	�g���q�̍폜
	*/
	iuFilePath	RemoveExtension(const char* extention=NULL) const
	{
		const char* const path = m_path.c_str();
		const char* const ext = strrchr(path, '.');
		if( ext == NULL ) return *this;
		if( extention != NULL )
		{
			if( !IsStringCaseEqual(ext+1, extention) ) return *this;
		}
		const size_t length = ext - path;
		return iuFilePath(std::string(path, length));
	}

	/**
	 * @brief	�f�B���N�g�����̍폜
	*/
	iuFilePath	RemoveDirectoryName(void) const
	{
		const char* const sep = FindLastPathSeparator();
		return sep != NULL ? iuFilePath(sep+1) : *this;
	}

	/**
	 * @brief	�t�@�C�����̍폜
	*/
	iuFilePath	RemoveFileName(void) const
	{
		const char* sep = FindLastPathSeparator();
		if( sep == NULL ) return GetRelativeCurrentDir();
		size_t length = sep - c_str() + 1;
		return iuFilePath(std::string(c_str(), length));
	}

	/**
	 * @brief	�t�H���_�̍쐬
	*/
	bool		CreateFolder(void) const
	{
#ifdef	IUTEST_OS_WINDOWS_MOBILE
#elif	IUTEST_OS_WINDOWS_MINGW
		if( mkdir(c_str()) == 0 ) return true;
#elif	IUTEST_OS_WINDOWS
		if( _mkdir(c_str()) == 0 ) return true;
#else
		if( mkdir(c_str(), 0777) == 0 ) return true;
#endif
		return DirectoryExists();
	}

	/**
	 * @brief	�t�H���_���ċA�I�ɍ쐬
	*/
	bool		CreateDirectoriesRecursively(void) const
	{
		if( !IsDirectory() ) return false;

		if( length() == 0 || DirectoryExists() ) return true;

		iuFilePath parent = RemoveTrailingPathSeparator().RemoveFileName();
		if( !parent.CreateDirectoriesRecursively() ) return false;
		return CreateFolder();
	}

	/**
	 * @brief	�t�@�C���܂��̓t�H���_�����݂��邩�ǂ���
	*/
	bool		FileOrDirectoryExists(void) const
	{
#if IUTEST_HAS_FILE_STAT
		posix::StatStruct file_stat;
		return posix::Stat(c_str(), &file_stat) == 0;
#endif
	}

	/**
	 * @brief	�t�H���_�����݂��邩�ǂ���
	*/
	bool		DirectoryExists(void) const
	{
#if IUTEST_HAS_FILE_STAT

#ifdef IUTEST_OS_WINDOWS
		const iuFilePath& path = IsRootDirectory() ? *this : RemoveTrailingPathSeparator();
#else
		const iuFilePath& path = *this;
#endif
		posix::StatStruct file_stat;
		if( posix::Stat(path.c_str(), &file_stat) == 0 )
		{
			return posix::IsDir(file_stat);
		}
#endif
		return false;
	}

	/**
	 * @brief	��Ԍ��̃p�X�Z�p���[�^�̃A�h���X���擾
	*/
	const char* FindLastPathSeparator(void) const
	{
		const char* ps = c_str();
		if( ps == NULL ) return NULL;
		const char* pe = ps + length() - 1;
		while( pe >= ps )
		{
			if( IsPathSeparator(*pe) )
			{
				if( (*(pe-1) & 0x80) == 0 )
				{
					return pe;
				}
				--pe;
			}
			--pe;
		}
		return NULL;
	}

public:
	/**
	 * @brief	�J�����g�f�B���N�g���̎擾
	*/
	static iuFilePath	GetCurrentDir(void)
	{
		return iuFilePath(internal::posix::GetCWD());
	}

	/**
	 * @brief	�J�����g�f�B���N�g���̑��΃p�X�擾
	*/
	static iuFilePath	GetRelativeCurrentDir(void)
	{
		std::string dir(".");
		dir += GetPathSeparator();
		return iuFilePath(dir);
	}

	/**
	 * @brief	���s�t�@�C���̃p�X���擾
	*/
	static iuFilePath	GetExecFilePath(void)
	{
#if		defined(IUTEST_OS_WINDOWS)
		char path[MAX_PATH];
		::GetModuleFileNameA(NULL, path, sizeof(path));
		return iuFilePath(path);
#elif	defined(IUTEST_OS_SOLARIS)
		return iuFilePath(getexecname());
#elif	defined(__FreeBSD__)
		int exe_path_mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, getpid() };
		char buf[1024];
		size_t length = 0;
		if( sysctl(exe_path_mib, 4, buf, &length, NULL, 0) != 0 ) return iuFilePath();
		return iuFilePath(buf);
#elif	defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN)
		char buf[1024];
		ssize_t len = ::readlink("/proc/self/exe", buf, sizeof(buf)-1);
		if( len == -1 ) return iuFilePath();
		buf[len] = '\0';
		return iuFilePath(buf);
#else
		return iuFilePath();
#endif
	}

	/**
	 * @brief	�p�X�̌���
	*/
	static iuFilePath	ConcatPaths(const iuFilePath& directory, const iuFilePath& relative_path)
	{
		std::string path = directory.RemoveTrailingPathSeparator().c_str();
		path += GetPathSeparator();
		path += relative_path.c_str();
		return iuFilePath(path);
	}

public:
	/**
	 * @brief	�p�X��؂蕶���̎擾
	*/
	static char	GetPathSeparator(void)
	{
#if IUTEST_OS_WINDOWS
		return '\\';
#else
		return '/';
#endif
	}

private:
	/**
	 * @biref	���K��
	*/
	void Normalize(void)
	{
		const char* src = c_str();
		if( src == NULL )
		{
			m_path = "";
			return;
		}

		char* const dst_top = new char [length()+1];
		char* dst = dst_top;

		while(*src != '\0')
		{
			*dst = *src;
			++src;
			while( IsPathSeparator(*src) )
			{
				++src;
			}
			++dst;
		}
	}

private:
	static bool IsPathSeparator(char c)
	{
#if IUTEST_OS_WINDOWS
		if( c == '\\' ) return true;
#endif
		return c == '/';
	}
private:
	std::string	m_path;
};

inline ::std::ostream& operator << (::std::ostream& os, const iuFilePath& path)
{
	return os << path.c_str();
}

}	// end of namespace detail

namespace internal
{
	// google test �Ƃ̌݊����̂���
	typedef detail::iuFilePath FilePath;
}

}	// end of namespace iutest

#endif
