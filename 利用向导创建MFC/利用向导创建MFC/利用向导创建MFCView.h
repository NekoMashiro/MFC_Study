
// 利用向导创建MFCView.h: C利用向导创建MFCView 类的接口
//

#pragma once


class C利用向导创建MFCView : public CView
{
protected: // 仅从序列化创建
	C利用向导创建MFCView() noexcept;
	DECLARE_DYNCREATE(C利用向导创建MFCView)

// 特性
public:
	C利用向导创建MFCDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C利用向导创建MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 利用向导创建MFCView.cpp 中的调试版本
inline C利用向导创建MFCDoc* C利用向导创建MFCView::GetDocument() const
   { return reinterpret_cast<C利用向导创建MFCDoc*>(m_pDocument); }
#endif

