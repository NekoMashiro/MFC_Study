
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystem.h"

#include "MainFrm.h"
#include "InfoFile.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "UserDlg.h"
#include "SellDlg.h"
#include "AddDlg.h"
#include "InfoDlg.h"
#include "DelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
	//产生WU_X消息，自动调用OnMyChange()函数
	ON_MESSAGE(WU_A, OnMyChange)
	ON_MESSAGE(WU_B, OnMyChange)
	ON_MESSAGE(WU_C, OnMyChange)
	ON_MESSAGE(WU_D, OnMyChange)
	ON_MESSAGE(WU_E, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::OnMenuXSGL)
	ON_COMMAND(ID_32772, &CMainFrame::OnMenuKCXX)
	ON_COMMAND(ID_32773, &CMainFrame::OnMenuKCTJ)
	ON_COMMAND(ID_32774, &CMainFrame::OnMenuKCSC)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_32775, &CMainFrame::OnMenuGRXX)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));


	//设置图标，IDI_ICON_WIN为图标资源的ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON,(long)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//设置右侧标题
	SetTitle(TEXT("技术支持QQ:847663935"));

	//设置窗口大小
	MoveWindow(0,0,800,500);
	//设置窗口居中
	CenterWindow();

	/*/测试CInfoFile类
	CInfoFile file;
	CString name, pwd;
	file.WritePwd("斧头帮帮主", "12333");
	file.ReadLogin(name, pwd);
	
	file.ReadDocline();

	MessageBox(name);
	MessageBox(pwd);
	*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//静态拆分窗口，1行2列,CSplitterWnd::CreateStatic
	m_Splitter.CreateStatic(this,1,2);
	//创建视图CSplitterWnd::CreateView
	//0，0	放在第0行第0列的位置
	//RUNTIME_CLASS(CSelectView) 需要头文件#include "SelectView.h"
	//CSelectView在SelectView.h中声明
	//CSize(200,500);	指定视图宽度和高度
	//pContext 为onCreateClient（）最后一个形参

	m_Splitter.CreateView(0,0,RUNTIME_CLASS(CSelectView),CSize(200,500),pContext);

	//0，1	放在第0行第1列的位置
	//RUNTIME_CLASS(CDisplayView) 需要头文件#include "DisplayView.h"
	m_Splitter.CreateView(0,1,RUNTIME_CLASS(CDisplayView),CSize(600,500),pContext);
	
	return TRUE;	//手工拆分框架，需要设置为TRUE 
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

LRESULT CMainFrame::OnMyChange( WPARAM wParam, LPARAM lParam )
{
	//
	CCreateContext context;
	if(WU_A == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_Splitter.GetPane(0,1);
		m_Splitter.DeleteView(0,1);
		m_Splitter.CreateView(0,1, RUNTIME_CLASS(CUserDlg),CSize(600,500),&context);
		CUserDlg *pNewView = (CUserDlg *)m_Splitter.GetPane(0,1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0,1);
	}
	if(WU_B == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_Splitter.GetPane(0,1);
		m_Splitter.DeleteView(0,1);
		m_Splitter.CreateView(0,1, RUNTIME_CLASS(CSellDlg),CSize(600,500),&context);
		CSellDlg *pNewView = (CSellDlg *)m_Splitter.GetPane(0,1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0,1);
	}
	if(WU_C == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_Splitter.GetPane(0,1);
		m_Splitter.DeleteView(0,1);
		m_Splitter.CreateView(0,1, RUNTIME_CLASS(CInfoDlg),CSize(600,500),&context);
		CInfoDlg *pNewView = (CInfoDlg *)m_Splitter.GetPane(0,1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0,1);
	}
	if(WU_D == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_Splitter.GetPane(0,1);
		m_Splitter.DeleteView(0,1);
		m_Splitter.CreateView(0,1, RUNTIME_CLASS(CAddDlg),CSize(600,500),&context);
		CAddDlg *pNewView = (CAddDlg *)m_Splitter.GetPane(0,1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0,1);
	}
	if(WU_E == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CDelDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_Splitter.GetPane(0,1);
		m_Splitter.DeleteView(0,1);
		m_Splitter.CreateView(0,1, RUNTIME_CLASS(CDelDlg),CSize(600,500),&context);
		CDelDlg *pNewView = (CDelDlg *)m_Splitter.GetPane(0,1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0,1);
	}
	return 0;
}


void CMainFrame::OnMenuXSGL() ///销售管理菜单
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_B, (WPARAM)WU_B, (LPARAM)0);
}


void CMainFrame::OnMenuKCXX() ///库存信息菜单
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_C, (WPARAM)WU_C, (LPARAM)0);
}


void CMainFrame::OnMenuKCTJ() ///库存添加菜单
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_D, (WPARAM)WU_D, (LPARAM)0);
}


void CMainFrame::OnMenuKCSC()///库存删除菜单
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_E, (WPARAM)WU_E, (LPARAM)0);
}


void CMainFrame::OnAppExit()
{
	exit(0);
}


void CMainFrame::OnMenuGRXX()
{
	//个人信息菜单
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_A, (WPARAM)WU_A, (LPARAM)0);
}
