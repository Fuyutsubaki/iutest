//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_constant.hpp
 * @brief		iris unit test �萔 ��` �t�@�C��
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
#ifndef INCG_IRIS_IUTEST_CONSTANT_HPP_37DDDC13_3259_42E0_A648_47B064DED4BA_
#define INCG_IRIS_IUTEST_CONSTANT_HPP_37DDDC13_3259_42E0_A648_47B064DED4BA_

//======================================================================
// include

namespace iutest {
namespace detail
{

namespace helper
{

/**
 * @brief	������萔
*/
template<typename DMY>
struct kStringsT
{
	static const char* const DefaultXmlReportFileName;	//!< �f�t�H���g xml �o�̓t�@�C����
	static const char* const UnkownFile;				//!< unkown file
	static const char* const Null;						//!< NULL
};

template<typename DMY>
const char* const kStringsT<DMY>::DefaultXmlReportFileName =  "test_detail.xml";
template<typename DMY>
const char* const kStringsT<DMY>::UnkownFile =  "unkown file";
template<typename DMY>
const char* const kStringsT<DMY>::Null =  "NULL";

#if IUTEST_HAS_LIB 

#if IUTEST_HAS_EXTERN_TEMPLATE

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()

extern template struct kStringsT<void>;

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()

#else

template struct kStringsT<void>;

#endif
#endif

}	// end of namespace helper

/** @internal */
typedef helper::kStringsT<void>	kStrings;

/**
 * @brief	�萔�Q
*/
struct kValues
{
#if defined(IUTEST_NO_INCLASS_MEMBER_INITIALIZATION)
	enum
	{
		MaxPrintContainerCount = 32
		, PrintArrayThreshold = 16
		, PrintArrayChunksize = PrintArrayThreshold/2
	};
#else
	static const size_t	MaxPrintContainerCount = 32;
	static const size_t	PrintArrayThreshold = 18;
	static const size_t	PrintArrayChunksize = PrintArrayThreshold/2;
#endif
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
