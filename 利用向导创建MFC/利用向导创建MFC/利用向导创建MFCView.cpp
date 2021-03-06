
// 利用向导创建MFCView.cpp: C利用向导创建MFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "利用向导创建MFC.h"
#endif

#include "利用向导创建MFCDoc.h"
#include "利用向导创建MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C利用向导创建MFCView

IMPLEMENT_DYNCREATE(C利用向导创建MFCView, CView)

BEGIN_MESSAGE_MAP(C利用向导创建MFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// C利用向导创建MFCView 构造/析构

C利用向导创建MFCView::C利用向导创建MFCView() noexcept
{
	// TODO: 在此处添加构造代码

}

C利用向导创建MFCView::~C利用向导创建MFCView()
{
}

BOOL C利用向导创建MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C利用向导创建MFCView 绘图

void C利用向导创建MFCView::OnDraw(CDC* pDC)
{
	C利用向导创建MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	pDC ->TextOutW(100, 100, TEXT("OnDraw"));
}


// C利用向导创建MFCView 打印

BOOL C利用向导创建MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C利用向导创建MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C利用向导创建MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C利用向导创建MFCView 诊断

#ifdef _DEBUG
void C利用向导创建MFCView::AssertValid() const
{
	CView::AssertValid();
}

void C利用向导创建MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C利用向导创建MFCDoc* C利用向导创建MFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C利用向导创建MFCDoc)));
	return (C利用向导创建MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// C利用向导创建MFCView 消息处理程序


void C利用向导创建MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	CString str;
	str.Format(TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(str, TEXT("鼠标左键单击"));
}
