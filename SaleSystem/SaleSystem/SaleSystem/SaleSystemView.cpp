
// SaleSystemView.cpp : CSaleSystemView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SaleSystem.h"
#endif

#include "SaleSystemDoc.h"
#include "SaleSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSaleSystemView

IMPLEMENT_DYNCREATE(CSaleSystemView, CView)

BEGIN_MESSAGE_MAP(CSaleSystemView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSaleSystemView ����/����

CSaleSystemView::CSaleSystemView()
{
	// TODO: �ڴ˴���ӹ������

}

CSaleSystemView::~CSaleSystemView()
{
}

BOOL CSaleSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSaleSystemView ����

void CSaleSystemView::OnDraw(CDC* /*pDC*/)
{
	CSaleSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSaleSystemView ��ӡ

BOOL CSaleSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSaleSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSaleSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSaleSystemView ���

#ifdef _DEBUG
void CSaleSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSaleSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSaleSystemDoc* CSaleSystemView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaleSystemDoc)));
	return (CSaleSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CSaleSystemView ��Ϣ�������
