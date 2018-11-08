// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��¼��ť����¼�
	UpdateData(TRUE);	//���༭�������ֵ��ͬ������������

	if(m_name.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("�û��������벻��Ϊ��"));
		return;
	}
	//��ȡ��ȷ��ֵ
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);

	if(name == m_name)	//�û���һ��
	{
		if(pwd == m_pwd)	//����һ��
		{
			//�رյ�ǰ����
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("�û������������"));
			return;
		}
	}
	else
	{
		MessageBox(TEXT("�û������������"));
		return;
	}

}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);	//�˳����򣬶����������˳���ǰ�Ĵ���
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��,//�������ļ��е��û������Զ����ص��༭��ؼ���
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);

	m_name = name;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CDialogEx::OnClose();
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	////CDialogEx::OnOK();
}
