#include <afxwin.h>	//mfcʹ�õ�ͷ�ļ�

class MyApp : public CWinApp	//CWinAppӦ�ó�����
{
public:
	//�������
	virtual BOOL InitInstance();

};

class MyFrame : public CFrameWnd	//���ڿ����
{
public:
	MyFrame();

	//������
	DECLARE_MESSAGE_MAP();
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnChar(UINT, UINT, UINT);
	afx_msg void OnPaint();
};