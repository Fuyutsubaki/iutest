//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_constant.h
 * @brief		iris unit test �萔 ��` �t�@�C��
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
#ifndef INCG_IRIS_iutest_constant_H_37DDDC13_3259_42e0_A648_47B064DED4BA_
#define INCG_IRIS_iutest_constant_H_37DDDC13_3259_42e0_A648_47B064DED4BA_

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
template<typename DMY=void>
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

}	// end of namespace helper

/** @internal */
typedef helper::kStringsT<>	kStrings;

/**
 * @brief	�萔�Q
*/
struct kValues
{
	static const size_t	MaxPrintContainerCount = 32;
	static const size_t	PrintArrayThreshold = 18;
	static const size_t	PrintArrayChunksize = PrintArrayThreshold/2;
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
