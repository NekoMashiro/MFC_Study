
// MainFrm.cpp : CMainFrame ���ʵ��
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

	//ON_MESSAGE��Ӧ�����Զ�����Ϣ
	//����WU_X��Ϣ���Զ�����OnMyChange()����
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));


	//����ͼ�꣬IDI_ICON_WINΪͼ����Դ��ID����ΪWINAPI����
	SetClassLong(m_hWnd, GCL_HICON,(long)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//�����Ҳ����
	SetTitle(TEXT("����֧��QQ:847663935"));

	//���ô��ڴ�С
	MoveWindow(0,0,800,500);
	//���ô��ھ���
	CenterWindow();

	/*/����CInfoFile��
	CInfoFile file;
	CString name, pwd;
	file.WritePwd("��ͷ�����", "12333");
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	//��̬��ִ��ڣ�1��2��,CSplitterWnd::CreateStatic
	m_Splitter.CreateStatic(this,1,2);
	//������ͼCSplitterWnd::CreateView
	//0��0	���ڵ�0�е�0�е�λ��
	//RUNTIME_CLASS(CSelectView) ��Ҫͷ�ļ�#include "SelectView.h"
	//CSelectView��SelectView.h������
	//CSize(200,500);	ָ����ͼ��Ⱥ͸߶�
	//pContext ΪonCreateClient�������һ���β�

	m_Splitter.CreateView(0,0,RUNTIME_CLASS(CSelectView),CSize(200,500),pContext);

	//0��1	���ڵ�0�е�1�е�λ��
	//RUNTIME_CLASS(CDisplayView) ��Ҫͷ�ļ�#include "DisplayView.h"
	m_Splitter.CreateView(0,1,RUNTIME_CLASS(CDisplayView),CSize(600,500),pContext);
	
	return TRUE;	//�ֹ���ֿ�ܣ���Ҫ����ΪTRUE 
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


void CMainFrame::OnMenuXSGL() ///���۹���˵�
{
	// TODO: �ڴ���������������
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_B, (WPARAM)WU_B, (LPARAM)0);
}


void CMainFrame::OnMenuKCXX() ///�����Ϣ�˵�
{
	// TODO: �ڴ���������������
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_C, (WPARAM)WU_C, (LPARAM)0);
}


void CMainFrame::OnMenuKCTJ() ///�����Ӳ˵�
{
	// TODO: �ڴ���������������
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_D, (WPARAM)WU_D, (LPARAM)0);
}


void CMainFrame::OnMenuKCSC()///���ɾ���˵�
{
	// TODO: �ڴ���������������
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_E, (WPARAM)WU_E, (LPARAM)0);
}


void CMainFrame::OnAppExit()
{
	exit(0);
}


void CMainFrame::OnMenuGRXX()
{
	//������Ϣ�˵�
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_A, (WPARAM)WU_A, (LPARAM)0);
}
