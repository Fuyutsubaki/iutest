//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_file.hpp
 * @brief		iris unit test �t�@�C���N���X �t�@�C��
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
#ifndef INCG_IRIS_iutest_file_HPP_77D2C2B9_F504_4bb5_BA56_D97A2EB37DC6_
#define INCG_IRIS_iutest_file_HPP_77D2C2B9_F504_4bb5_BA56_D97A2EB37DC6_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include "iutest_stream.hpp"

namespace iutest
{

//======================================================================
// declare
class IFile;

//======================================================================
// class
namespace detail
{

/**
 * @brief	�t�@�C�������N���X�C���^�[�t�F�C�X
*/
class IFileSystem
{
	template<typename T>
	struct Variable
	{
		static IFileSystem*	m_pInstance;
	};

	typedef Variable<void>	var;
public:
	IFileSystem(void)
	{
		var::m_pInstance = this;
	}
	virtual ~IFileSystem(void)
	{
		var::m_pInstance = NULL;
	}

public:
	virtual void	Initialize(void) {}

public:
	static IFileSystem*	GetInstance(void)	{ return var::m_pInstance; }

public:
	static IFile*	New(void)
	{
		IFileSystem* fs = GetInstance();
		if( fs == NULL ) return NULL;
		IFile* p = fs->Create();
		return p;
	}
	static void		Free(IFile* ptr)
	{
		IFileSystem* fs = GetInstance();
		if( fs == NULL ) return;
		fs->Delete(ptr);
	}

private:
	virtual IFile*	Create(void) = 0;
	virtual void	Delete(IFile*) = 0;
};

}	// end of namespace detail
}	// end of namespace iutest

template<typename T>
::iutest::detail::IFileSystem* ::iutest::detail::IFileSystem::Variable<T>::m_pInstance = NULL;

namespace iutest
{

/**
 * @brief	�t�@�C���N���X�C���^�[�t�F�C�X
*/
class IFile : public detail::IOutStream
{
public:
	enum OpenFlag
	{
		OpenRead		= 0x00000001,	//!< �ǂݍ���
		OpenWrite		= 0x00000002,	//!< ��������
		OpenReadWrite	= 0x00000003	//!< �ǂݏ���
	};
public:
	virtual ~IFile(void) {}
public:
	//! �J��
	virtual	bool	Open(const char* filename, int mode) = 0;
	//! ����
	virtual	void	Close(void)	= 0;
};

/**
 * @brief	�t�@�C�������N���X�C���^�[�t�F�C�X
*/
template<typename FILE>
class FileSystem : public detail::IFileSystem
{
private:
	virtual IFile*	Create(void) IUTEST_CXX_OVERRIDE		{ return new FILE; }
	virtual void	Delete(IFile* ptr) IUTEST_CXX_OVERRIDE	{ detail::Delete<FILE>(static_cast<FILE*>(ptr)); }
};


#if IUTEST_HAS_FOPEN

/**
 * @brief	�W���t�@�C���N���X
*/
class StdioFile : public IFile
{
	FILE* m_fp;
public:
	StdioFile(void) IUTEST_CXX_NOEXCEPT_SPEC : m_fp(NULL) {}
	virtual ~StdioFile(void) { Close(); }
public:
	/**
	 * @brief	�J��
	 * @param [in]	filename	= �t�@�C���p�X
	 * @param [in]	mode		= ���[�h
	 * @return	����
	*/
	virtual	bool	Open(const char* filename, int mode) IUTEST_CXX_OVERRIDE
	{
		Close();
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
		switch( mode )
		{
		case IFile::OpenRead:
			m_fp = fopen(filename, "rb");
			break;
		case IFile::OpenWrite:
			m_fp = fopen(filename, "wb");
			break;
		case IFile::OpenReadWrite:
			m_fp = fopen(filename, "ab");
			break;
		}
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
		return m_fp != NULL;
	}
	/**
	 * @brief	����
	*/
	virtual	void	Close(void) IUTEST_CXX_OVERRIDE
	{
		if( m_fp != NULL )
		{
			fclose(m_fp);
			m_fp = NULL;
		}
	}
	/**
	 * @brief	��������
	 * @param [in]	buf		= �������݃o�b�t�@
	 * @param [in]	size	= �o�b�t�@�T�C�Y
	 * @param [in]	cnt		= �������݉�
	*/
	virtual void	Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
	{
		fwrite(buf, size, cnt, m_fp);
	}
};

#endif

#if IUTEST_HAS_STRINGSTREAM

class StringStreamFile : public IFile
{
public:
	/**
	 * @brief	�J��
	 * @param [in]	filename	= unused
	 * @param [in]	mode		= unused
	 * @return	����
	*/
	virtual	bool	Open(const char* , int ) IUTEST_CXX_OVERRIDE
	{
		ss.clear();
		return true;
	}

	/**
	 * @brief	����
	*/
	virtual	void	Close(void) IUTEST_CXX_OVERRIDE
	{
	}

	/**
	 * @brief	��������
	 * @param [in]	buf		= �������݃o�b�t�@
	 * @param [in]	size	= �o�b�t�@�T�C�Y
	 * @param [in]	cnt		= �������݉�
	*/
	virtual void	Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
	{
		for( size_t i=0; i < cnt; ++i )
			ss.write(static_cast<const char*>(buf), size);
	}

protected:
	::std::stringstream ss;
};

#endif

}	// end of namespace iutest

#endif
