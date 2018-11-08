// SelectView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SelectView.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView ���

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView ��Ϣ�������


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//ͼ����Դ�ļ���CWinApp::LoadIcon
	//IDI_ICON_REΪͼ����Դ��ID
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);

	//ͼƬ�б�Ĵ���CImageList::Create
	//30,30	ָ��ͼ��Ŀ�Ⱥ͸߶�
	//ILC_COLOR32	ͼ���ʽ
	//1��1	�ж���ͼ���д���ٸ�
	m_imageList.Create(30,30,ILC_COLOR32,1,1);

	//ͼƬ�б����ͼ��CImageList::Add
	m_imageList.Add(icon);

	//��ȡ��ͼ�����ؼ�CImageList::GetTreeCtrl
	m_treeCtrl = &GetTreeCtrl();

	//���ؼ�����ͼƬ�б�CTreeCtrl::SetImageList
	m_treeCtrl->SetImageList(&m_imageList,TVSIL_NORMAL);

	//���ؼ����ýڵ�CTreeCtrl::InsertItem
	m_treeCtrl->InsertItem(TEXT("������Ϣ"),0,0,NULL);
	m_treeCtrl->InsertItem(TEXT("���۹���"),0,0,NULL);
	m_treeCtrl->InsertItem(TEXT("�����Ϣ"),0,0,NULL);
	m_treeCtrl->InsertItem(TEXT("������"),0,0,NULL);
	m_treeCtrl->InsertItem(TEXT("���ɾ��"),0,0,NULL);



}

//ָʾѡ�����Ѵ�һ��תΪ��һ��
void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//��ȡ��ǰѡ����
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	// ͨ��ѡ�е����ȡѡ���������
	CString str = m_treeCtrl->GetItemText(item);
	////MessageBox(str);
	if(str==TEXT("������Ϣ"))
	{
		//��Ҫ���������ͷ�ļ�#include "MainFrm.h"
		//CWnd::PostMessage ��һ����Ϣ���뵽���ڵ���Ϣ����
		//AfxGetMainWnd();	��ܴ��ڶ����ָ��
		//AfxGetMainWnd().GetSafeHwnd();��ȡ���ش��ڵľ����CWnd::GetSafeHwnd
		//WM_A	�Զ�����Ϣ
		//(WPARAM)WU_A	ָ���˸��ӵ���Ϣ��Ϣ
		//(LPARAM)0		ָ���˸��ӵ���Ϣ��Ϣ���˲�������û�����塣
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_A, (WPARAM)WU_A, (LPARAM)0);
	}
	if(str==TEXT("���۹���"))
	{
		//��Ҫ���������ͷ�ļ�#include "MainFrm.h"
		//CWnd::PostMessage ��һ����Ϣ���뵽���ڵ���Ϣ����
		//AfxGetMainWnd();	��ܴ��ڶ����ָ��
		//AfxGetMainWnd().GetSafeHwnd();��ȡ���ش��ڵľ����CWnd::GetSafeHwnd
		//WM_A	�Զ�����Ϣ
		//(WPARAM)WU_A	ָ���˸��ӵ���Ϣ��Ϣ
		//(LPARAM)0		ָ���˸��ӵ���Ϣ��Ϣ���˲�������û�����塣
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_B, (WPARAM)WU_B, (LPARAM)0);
	}
	if(str==TEXT("�����Ϣ"))
	{
		//��Ҫ���������ͷ�ļ�#include "MainFrm.h"
		//CWnd::PostMessage ��һ����Ϣ���뵽���ڵ���Ϣ����
		//AfxGetMainWnd();	��ܴ��ڶ����ָ��
		//AfxGetMainWnd().GetSafeHwnd();��ȡ���ش��ڵľ����CWnd::GetSafeHwnd
		//WM_A	�Զ�����Ϣ
		//(WPARAM)WU_A	ָ���˸��ӵ���Ϣ��Ϣ
		//(LPARAM)0		ָ���˸��ӵ���Ϣ��Ϣ���˲�������û�����塣
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_C, (WPARAM)WU_C, (LPARAM)0);
	}
	if(str==TEXT("������"))
	{
		//��Ҫ���������ͷ�ļ�#include "MainFrm.h"
		//CWnd::PostMessage ��һ����Ϣ���뵽���ڵ���Ϣ����
		//AfxGetMainWnd();	��ܴ��ڶ����ָ��
		//AfxGetMainWnd().GetSafeHwnd();��ȡ���ش��ڵľ����CWnd::GetSafeHwnd
		//WM_A	�Զ�����Ϣ
		//(WPARAM)WU_A	ָ���˸��ӵ���Ϣ��Ϣ
		//(LPARAM)0		ָ���˸��ӵ���Ϣ��Ϣ���˲�������û�����塣
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_D, (WPARAM)WU_D, (LPARAM)0);
	}
	if(str==TEXT("���ɾ��"))
	{
		//��Ҫ���������ͷ�ļ�#include "MainFrm.h"
		//CWnd::PostMessage ��һ����Ϣ���뵽���ڵ���Ϣ����
		//AfxGetMainWnd();	��ܴ��ڶ����ָ��
		//AfxGetMainWnd().GetSafeHwnd();��ȡ���ش��ڵľ����CWnd::GetSafeHwnd
		//WM_A	�Զ�����Ϣ
		//(WPARAM)WU_A	ָ���˸��ӵ���Ϣ��Ϣ
		//(LPARAM)0		ָ���˸��ӵ���Ϣ��Ϣ���˲�������û�����塣
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WU_E, (WPARAM)WU_E, (LPARAM)0);
	}
}
