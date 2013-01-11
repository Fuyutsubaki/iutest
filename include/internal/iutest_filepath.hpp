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
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_filepath_HPP_D69E7545_BF8A_4edc_9493_9105C69F9378_
#define INCG_IRIS_iutest_filepath_HPP_D69E7545_BF8A_4edc_9493_9105C69F9378_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// include
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
	bool	IsDirectory(void) const;

	/**
	 * @brief	���[�g�f�B���N�g���p�X���ǂ���
	*/
	bool	IsRootDirectory(void) const;

	/**
	 * @brief	��΃p�X���ǂ���
	*/
	bool	IsAbsolutePath(void) const;

	/**
	 * @brief	�����̃Z�p���[�^�[���폜
	*/
	iuFilePath	RemoveTrailingPathSeparator(void) const;

	/**
	 * @brief	�g���q�̍폜
	*/
	iuFilePath	RemoveExtension(const char* extention=NULL) const;

	/**
	 * @brief	�f�B���N�g�����̍폜
	*/
	iuFilePath	RemoveDirectoryName(void) const;

	/**
	 * @brief	�t�@�C�����̍폜
	*/
	iuFilePath	RemoveFileName(void) const;

	/**
	 * @brief	�t�H���_�̍쐬
	*/
	bool		CreateFolder(void) const;

	/**
	 * @brief	�t�H���_���ċA�I�ɍ쐬
	*/
	bool		CreateDirectoriesRecursively(void) const;

	/**
	 * @brief	�t�@�C���܂��̓t�H���_�����݂��邩�ǂ���
	*/
	bool		FileOrDirectoryExists(void) const;

	/**
	 * @brief	�t�H���_�����݂��邩�ǂ���
	*/
	bool		DirectoryExists(void) const;

	/**
	 * @brief	��Ԍ��̃p�X�Z�p���[�^�̃A�h���X���擾
	*/
	const char* FindLastPathSeparator(void) const;

public:
	/**
	 * @brief	�J�����g�f�B���N�g���̎擾
	*/
	static iuFilePath	GetCurrentDir(void);

	/**
	 * @brief	�J�����g�f�B���N�g���̑��΃p�X�擾
	*/
	static iuFilePath	GetRelativeCurrentDir(void);

	/**
	 * @brief	���s�t�@�C���̃p�X���擾
	*/
	static iuFilePath	GetExecFilePath(void);

	/**
	 * @brief	�p�X�̌���
	*/
	static iuFilePath	ConcatPaths(const iuFilePath& directory, const iuFilePath& relative_path);

public:
	/**
	 * @brief	�p�X��؂蕶���̎擾
	*/
	static char	GetPathSeparator(void);

private:
	/**
	 * @biref	���K��
	*/
	void Normalize(void);

private:
	static bool IsPathSeparator(char c);
private:
	std::string	m_path;
};

inline iu_ostream& operator << (iu_ostream& os, const iuFilePath& path)
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

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_filepath.ipp"
#endif

#endif

#endif
