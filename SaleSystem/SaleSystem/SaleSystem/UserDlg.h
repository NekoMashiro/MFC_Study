#pragma once



// CUserDlg ������ͼ

class CUserDlg : public CFormView
{
	DECLARE_DYNCREATE(CUserDlg)

protected:
	CUserDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CUserDlg();

public:
	enum { IDD = DIALOG_USER };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_user;
	CString m_name;
	CString m_newPwd;
	CString m_surePwd;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
};


