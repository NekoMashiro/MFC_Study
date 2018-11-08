// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "MainFrm.h"
#include "UserDlg.h"
#include "InfoFile.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(CUserDlg::IDD)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg ���

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg ��Ϣ�������


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ��
	m_user = TEXT("����Ա");
	CString name,pwd;
	CInfoFile file;
	file.ReadLogin(name, pwd);
	
	m_name = name;
	UpdateData(FALSE);	//��������ֵ��ͬ�����ؼ�����

}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������룬��Ϊȷ����ť
	UpdateData(TRUE); //�õ����µ�ֵ�����ؼ��������ó������������

	if(m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("���벻��Ϊ�գ�"));
		return;
	}
	if(m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("��������ȷ�����벻һ�£�"));
		return;
	}

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);
	if(m_surePwd == pwd)
	{
		MessageBox(TEXT("�����벻����ԭ����һ��"));
		return;
	}

	//CString  ת��Ϊchar *
	CStringA t_name, t_surePwd;
	t_name = name;
	t_surePwd = m_surePwd;
	file.WritePwd(t_name.GetBuffer(), t_surePwd.GetBuffer());
	MessageBox(TEXT("�����޸ĳɹ���"));

	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);	//��������ֵ��ͬ�����ؼ�����
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������룬��Ϊȡ����ť

	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);	//��������ֵ��ͬ�����ؼ�����

}

