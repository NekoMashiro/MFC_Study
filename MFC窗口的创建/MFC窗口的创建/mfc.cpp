#include "mfc.h"

MyApp app; //ȫ��Ӧ�ó���������ҽ���һ��

BOOL MyApp::InitInstance()
{
	//��������
	MyFrame* frame = new MyFrame;
	//��ʾ�����
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	m_pMainWnd = frame;	//ָ�������ڵ�ָ��

	return TRUE;	//���������ĳ�ʼ��
}

//�ֽ��
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()	//����������
	ON_WM_CHAR()	//���̰���
	ON_WM_PAINT()	//��ͼ
END_MESSAGE_MAP()

MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC���ڵĴ���"));
}

void MyFrame::OnLButtonDown(UINT, CPoint point)
{
	/*
	TCHAR buf[1024];
	wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(buf, TEXT("����������λ��"));
	*/

	//mfc�е��ַ���	CString
	CString str;
	str.Format(TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(str, TEXT("MFC�е��ַ��� CString"));

}

void MyFrame::OnChar(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("������ %c"), key);

	MessageBox(str, TEXT("���̰���"));
}

void MyFrame::OnPaint()
{
	CPaintDC dc(this);
	//������
	//dc.TextOutW(100, 100, TEXT("MFC���ڵĴ���"));
	//����Բ
	dc.Ellipse(10, 10, 100, 200);
}
