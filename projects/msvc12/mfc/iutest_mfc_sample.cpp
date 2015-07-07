// iutest_mfc_sample.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "iutest_mfc_sample.h"
#include "iutest.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �B��̃A�v���P�[�V���� �I�u�W�F�N�g�ł��B

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC �����������āA�G���[�̏ꍇ�͌��ʂ�������܂��B
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
			_tprintf(_T("�v���I�ȃG���[: MFC �̏��������ł��܂���ł����B\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �A�v���P�[�V�����̓�����L�q����R�[�h�������ɑ}�����Ă��������B
			IUTEST_INIT(&argc, argv);
			nRetCode = IUTEST_RUN_ALL_TESTS();
		}
	}
	else
	{
		// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
		_tprintf(_T("�v���I�ȃG���[: GetModuleHandle �����s���܂���\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

IUTEST(MFC, String)
{
	CString str = _T("Test");
	IUTEST_ASSERT_EQ(_T("Test"), str);
	IUTEST_ASSERT_STREQ(_T("Test"), str);
	IUTEST_ASSERT_STREQ(str, str);

	IUTEST_ASSERT_STRIN(str, _T("Test"));
}

IUTEST(MFC, Rect)
{
	CRect r = { 0, 0, 100, 100 };
	IUTEST_ASSERT_EQ(r, r);
}

IUTEST(MFC, List)
{
	int a[10];
	CList<int> list;
	for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
	{
		a[i] = i;
		list.AddTail(i);
	}
	//IUTEST_ASSERT_EQ_COLLECTIONS(list.GetHeadPosition(), list.GetTailPosition(), ::std::begin(a), ::std::end(b));
}
