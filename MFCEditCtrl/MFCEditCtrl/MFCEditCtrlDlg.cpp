
// MFCEditCtrlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCEditCtrl.h"
#include "MFCEditCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCEditCtrlDlg 对话框



CMFCEditCtrlDlg::CMFCEditCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCEDITCTRL_DIALOG, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCEditCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_text);
}

BEGIN_MESSAGE_MAP(CMFCEditCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCEditCtrlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCEditCtrlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCEditCtrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCEditCtrlDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCEditCtrlDlg 消息处理程序

BOOL CMFCEditCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//默认第一个编辑框有内容
	m_edit1.SetWindowTextW(TEXT("fkig"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCEditCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCEditCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCEditCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCEditCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 获取m_edit1的内容
	CString str;
	m_edit1.GetWindowTextW(str);

	// 将内容给予m_edit2
	m_edit2.SetWindowTextW(str);
}


void CMFCEditCtrlDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	// 按键后退出
	CDialog::OnOK();	// 按确定退出对话框
	//CDialog::OnCancel()	// 按取消退出对话框

}


void CMFCEditCtrlDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}

/*
BOOL UpdateData(
   BOOL bSaveAndValidate = TRUE
);

bSaveAndValidate
标记指示是否对话框初始化( FALSE)或数据检索 ( TRUE)。

*/
void CMFCEditCtrlDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 利用关联value的方式设置和改变edit的内容


	// 设置内容
	m_text = TEXT("sbig");

	//将变量内容同步到控件中
	UpdateData(FALSE);
}


void CMFCEditCtrlDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取内容 将控件内容同步到变量中
	UpdateData(TRUE);
	MessageBox(m_text);
}
