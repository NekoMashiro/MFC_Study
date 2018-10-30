#include <Windows.h>	//底层窗口实现的头文件
#include <windowsx.h>

//CALLBACK 代表_stdcall 参数的传递顺序：从右到左依次入栈，函数返回前清空堆栈
LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,	//消息所属窗口句柄
	_In_ UINT   uMsg,	//具体消息名称 WM_XXXX 消息名
	_In_ WPARAM wParam,	//鼠标附加消息
	_In_ LPARAM lParam)	//键盘附加消息
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);	//DestroyWindow 发送另一个消息：WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:	//鼠标左键按下
		int xPOS = GET_X_LPARAM(lParam);
		int yPOS = GET_Y_LPARAM(lParam);
		//xPOS yPOS记录鼠标点击的x y位置
		/*
		int WINAPI MessageBox(
			_In_opt_ HWND    hWnd,	生成弹窗的窗口的句柄
			_In_opt_ LPCTSTR lpText,	弹窗内容
			_In_opt_ LPCTSTR lpCaption,	弹窗标题
			_In_     UINT    uType);	弹窗的按钮
		*/
		char buf[64];
		wsprintf(buf, TEXT("x = %d, y = %d"), xPOS, yPOS);	//拼接字符串
		MessageBox(hwnd, buf, TEXT("鼠标左键按下位置"), MB_OK);
		break;
	case WM_KEYDOWN:	//按下键盘
		MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Hello World"), strlen("Hello World"));
		EndPaint(hwnd, &ps);
		break;
	}
	//返回值用默认处理方式
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//程序函数入口


//WINAPI 代表_stdcall 参数的传递顺序：从右到左依次入栈，函数返回前清空堆栈
int WINAPI WinMain(
	HINSTANCE hInstance,	//应用程序实例句柄
	HINSTANCE hPervInstance,	//上一个应用程序句柄，在win32环境下参数一般为null 不起作用
	LPSTR lpCmdline,	//char * avgr[]
	int nShowCmd)	//显示命令：最大化 最小化 正常
{
	//1.设计窗口
	WNDCLASS wc;
	wc.cbClsExtra = 0;	//类的额外内存
	wc.cbWndExtra = 0;	//窗口的额外内存
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//窗口背景
	wc.hCursor = LoadCursor(NULL, IDC_HAND);	//设置光标，如果第一个值为NULL，代表使用系统提供的光标
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);	//设置图标，如果第一个值为NULL，戴白哦使用系统提供的图标
	wc.hInstance = hInstance;	//应用程序实例句柄，传入WinMain中的形参即可
	wc.lpfnWndProc = WindowProc;	//回调函数 窗口过程
	wc.lpszClassName = TEXT("底层窗口的实现");	//指定窗口类名称
	wc.lpszMenuName = NULL;	//菜单名称
	wc.style = 0;	//显示风格 0代表默认风格

	//2.注册窗口
	RegisterClass(&wc);

	//3.创建窗口
	/*
	lpClassName,	类名
	lpWindowName,	标题名
	dwStyle,	风格 常用WS_OVERLAPPEDWINDOW
	x,
	y,	显示坐标
	nWidth,
	nHeight,	宽高 CW_USEDEFAULT 默认值
	hWndParent,	父窗口 NULL
	hMenu,	菜单 NULL
	hInstance,	实例句柄 hInstance
	lpParam	附加值 鼠标附加值 NULL
	*/
	HWND hwnd;
	hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("WINDOWS"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//4.显示与更新
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//5.通过循环取消息
	/*
	HWND        hwnd;	主窗口句柄
	UINT        message;	具体消息名称
	WPARAM      wParam;	附加消息 键盘消息
	LPARAM      lParam; 附加消息 鼠标消息 左右键
	DWORD       time;	消息产生时间
	POINT       pt;		附加消息 鼠标信息 x y
	*/
	MSG msg;

	while (1)
	{
		/*
			_Out_ LPMSG lpMsg,	封装好的消息指针
			_In_opt_ HWND hWnd,	捕获消息的窗口 填NULL代表捕获所有窗口
			_In_ UINT wMsgFilterMin,		最小和最大的过滤消息，一般填零，代表捕获所有的消息
			_In_ UINT wMsgFilterMax);
		*/
		if (GetMessage(&msg, NULL, 0, 0) == FALSE)
			break;
		//翻译消息 处理组合键 如ctrl+C
		TranslateMessage(&msg);
		//分发消息
		DispatchMessage(&msg);
	}

	//6.处理窗口过程


	return 0;
}