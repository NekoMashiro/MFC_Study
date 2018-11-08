#pragma once
#include "afxwin.h"



// CSellDlg ������ͼ

class CSellDlg : public CFormView
{
	DECLARE_DYNCREATE(CSellDlg)

protected:
	CSellDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSellDlg();

public:
	enum { IDD = DIALOG_SELL };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CComboBox m_combo;
	int m_price;
	int m_left;
	int m_num;
	CString m_sellInfo;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
};


