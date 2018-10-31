#include <afxwin.h>	//mfc使用的头文件

class MyApp : public CWinApp	//CWinApp应用程序类
{
public:
	//程序入口
	virtual BOOL InitInstance();

};

class MyFrame : public CFrameWnd	//窗口框架类
{
public:
	MyFrame();

	//声明宏
	DECLARE_MESSAGE_MAP();
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnChar(UINT, UINT, UINT);
	afx_msg void OnPaint();
};