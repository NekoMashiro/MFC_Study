
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

//WM_USER		���û��Զ�����Ϣ��һ����ʼֵ
//WM_USER+100	��Ϊ������ϵͳ��Ϣ���û���Ϣ�������ͻ
#define WU_A	WM_USER+100	
#define WU_B	WM_USER+101	
#define WU_C	WM_USER+102	
#define WU_D	WM_USER+103	
#define WU_E	WM_USER+104	

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


private:
	CSplitterWnd m_Splitter;		//�зִ��������
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMenuXSGL();
	afx_msg void OnMenuKCXX();
	afx_msg void OnMenuKCTJ();
	afx_msg void OnMenuKCSC();
	afx_msg void OnAppExit();
	afx_msg void OnMenuGRXX();
};


