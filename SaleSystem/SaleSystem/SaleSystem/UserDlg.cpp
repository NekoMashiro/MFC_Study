// UserDlg.cpp : 实现文件
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


// CUserDlg 诊断

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


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化
	m_user = TEXT("销售员");
	CString name,pwd;
	CInfoFile file;
	file.ReadLogin(name, pwd);
	
	m_name = name;
	UpdateData(FALSE);	//将变量的值，同步到控件里面

}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码，此为确定按钮
	UpdateData(TRUE); //拿到最新的值，将控件的内容拿出放入变量里面

	if(m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("密码不能为空！"));
		return;
	}
	if(m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确认密码不一致！"));
		return;
	}

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);
	if(m_surePwd == pwd)
	{
		MessageBox(TEXT("新密码不能与原密码一样"));
		return;
	}

	//CString  转换为char *
	CStringA t_name, t_surePwd;
	t_name = name;
	t_surePwd = m_surePwd;
	file.WritePwd(t_name.GetBuffer(), t_surePwd.GetBuffer());
	MessageBox(TEXT("密码修改成功！"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);	//将变量的值，同步到控件里面
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码，此为取消按钮

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);	//将变量的值，同步到控件里面

}

