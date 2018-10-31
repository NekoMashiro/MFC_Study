#include "mfc.h"

MyApp app; //全局应用程序对象，有且仅有一个

BOOL MyApp::InitInstance()
{
	//创建窗口
	MyFrame* frame = new MyFrame;
	//显示与更新
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	m_pMainWnd = frame;	//指向主窗口的指针

	return TRUE;	//返回正常的初始化
}

//分界宏
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()	//鼠标左键按下
	ON_WM_CHAR()	//键盘按下
	ON_WM_PAINT()	//绘图
END_MESSAGE_MAP()

MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC窗口的创建"));
}

void MyFrame::OnLButtonDown(UINT, CPoint point)
{
	/*
	TCHAR buf[1024];
	wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(buf, TEXT("鼠标左键按下位置"));
	*/

	//mfc中的字符串	CString
	CString str;
	str.Format(TEXT("x = %d, y = %d"), point.x, point.y);
	MessageBox(str, TEXT("MFC中的字符串 CString"));

}

void MyFrame::OnChar(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("按下了 %c"), key);

	MessageBox(str, TEXT("键盘按下"));
}

void MyFrame::OnPaint()
{
	CPaintDC dc(this);
	//画文字
	//dc.TextOutW(100, 100, TEXT("MFC窗口的创建"));
	//画椭圆
	dc.Ellipse(10, 10, 100, 200);
}
