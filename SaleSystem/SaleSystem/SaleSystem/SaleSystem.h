
// SaleSystem.h : SaleSystem Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSaleSystemApp:
// �йش����ʵ�֣������ SaleSystem.cpp
//

class CSaleSystemApp : public CWinApp
{
public:
	CSaleSystemApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSaleSystemApp theApp;
