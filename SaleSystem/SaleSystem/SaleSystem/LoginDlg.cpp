// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg 对话框

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


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//登录按钮点击事件
	UpdateData(TRUE);	//将编辑框里面的值，同步到变量里面

	if(m_name.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名或密码不能为空"));
		return;
	}
	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);

	if(name == m_name)	//用户名一致
	{
		if(pwd == m_pwd)	//密码一致
		{
			//关闭当前窗口
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("用户名或密码错误"));
			return;
		}
	}
	else
	{
		MessageBox(TEXT("用户名或密码错误"));
		return;
	}

}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);	//退出程序，而不仅仅是退出当前的窗口
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化,//将配置文件中的用户名，自动加载到编辑框控件中
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);

	m_name = name;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	////CDialogEx::OnOK();
}
