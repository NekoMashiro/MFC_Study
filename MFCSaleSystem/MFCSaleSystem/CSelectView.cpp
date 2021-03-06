// CSelectView.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCSaleSystem.h"
#include "CSelectView.h"
#include "MainFrm.h";


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


// CSelectView 诊断

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


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	// 初始化 树视图
	
	// 1.获取树控件
	treeCtrl = &GetTreeCtrl();

	// 2.准备图片集合
	HICON icon = AfxGetApp()->LoadIconW(IDI_SNOW);

	imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	imageList.Add(icon);

	treeCtrl->SetImageList(&imageList, TVSIL_NORMAL);

	// 3.添加节点
	treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
	treeCtrl->InsertItem(TEXT("销售管理"), 0, 0, NULL);
	treeCtrl->InsertItem(TEXT("库存信息"), 0, 0, NULL);
	treeCtrl->InsertItem(TEXT("库存添加"), 0, 0, NULL);
	treeCtrl->InsertItem(TEXT("删除商品"), 0, 0, NULL);
}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	// 获取当前选中项
	HTREEITEM item = treeCtrl->GetSelectedItem();
	CString str = treeCtrl->GetItemText(item);

	//MessageBox(str);
	
	if (str == TEXT("个人信息") )
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
}
