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
}strAllData[5]={{1,"��ĳ",30, 10},{2,"��ĳ",40, 45},{3, "��ĳ",32, 27},{4,"��ĳ",20, 25},{5,"��ĳ",36, 35}};
*/
//ȫ������


// CInfoDlg ������ͼ

class CInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CInfoDlg)

protected:
	CInfoDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInfoDlg();

public:
	CSortList m_list;
	enum { IDD = DIALOG_INFO };
	static int CALLBACK FileListCompareFunction(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);//�ú��������Ǿ�̬����ȫ�ֺ���
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);

};

