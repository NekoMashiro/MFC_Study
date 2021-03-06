// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCSaleSystem.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, login_user(_T(""))
	, login_password(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, login_user);
	DDX_Text(pDX, IDC_EDIT2, login_password);
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
	// 点击登录按钮
	UpdateData(TRUE);
	
	// 若为空
	if (login_user.IsEmpty() || login_password.IsEmpty())
	{
		MessageBox(TEXT("用户名或密码不能为空！"), TEXT("登入失败"), MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 获取正确的登录信息
	CInfoFile file;
	CString user, password;
	file.ReadLogin(user, password);

	if (user == login_user)	// 用户名一致
		if (password == login_password)
			// 密码一致 关闭当前对话框
			CDialog::OnOK();
		else
			// 密码不一致 弹出错误
			MessageBox(TEXT("密码错误！"), TEXT("登入失败"), MB_ICONEXCLAMATION | MB_OK);
	else
		// 用户名不一致
		MessageBox(TEXT("用户名不存在！"), TEXT("登入失败"), MB_ICONEXCLAMATION | MB_OK);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 默认登录信息
	CInfoFile file;
	CString user, password;
	file.ReadLogin(user, password);
	login_user = user;
	login_password = password;

	// 同步至控件中
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// 点击取消按钮
	exit(0);
	// TODO: 在此添加控件通知处理程序代码
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// 按下回车时不进入，则删除 CDialogEx::OnOK();

	// CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 按下回车时不关闭当前对话框，而是退出程序，删除 CDialogEx::OnClose();
	exit(0);

	// CDialogEx::OnClose();
}
