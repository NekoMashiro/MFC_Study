#pragma once
#include "afxcmn.h"
#include "SortList.h"
/*
struct DEMO_DATA
{
	int id;
	char szName[20];
	int iAge;
	int price;
}strAllData[5]={{1,"王某",30, 10},{2,"张某",40, 45},{3, "武某",32, 27},{4,"陈某",20, 25},{5,"李某",36, 35}};
*/
//全局数据


// CInfoDlg 窗体视图

class CInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CInfoDlg)

protected:
	CInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CInfoDlg();

public:
	CSortList m_list;
	enum { IDD = DIALOG_INFO };
	static int CALLBACK FileListCompareFunction(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);//该函数必须是静态或者全局函数
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);

};

