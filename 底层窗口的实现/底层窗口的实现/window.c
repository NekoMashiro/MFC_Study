#include <Windows.h>	//�ײ㴰��ʵ�ֵ�ͷ�ļ�
#include <windowsx.h>

//CALLBACK ����_stdcall �����Ĵ���˳�򣺴��ҵ���������ջ����������ǰ��ն�ջ
LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,	//��Ϣ�������ھ��
	_In_ UINT   uMsg,	//������Ϣ���� WM_XXXX ��Ϣ��
	_In_ WPARAM wParam,	//��긽����Ϣ
	_In_ LPARAM lParam)	//���̸�����Ϣ
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);	//DestroyWindow ������һ����Ϣ��WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:	//����������
		int xPOS = GET_X_LPARAM(lParam);
		int yPOS = GET_Y_LPARAM(lParam);
		//xPOS yPOS��¼�������x yλ��
		/*
		int WINAPI MessageBox(
			_In_opt_ HWND    hWnd,	���ɵ����Ĵ��ڵľ��
			_In_opt_ LPCTSTR lpText,	��������
			_In_opt_ LPCTSTR lpCaption,	��������
			_In_     UINT    uType);	�����İ�ť
		*/
		char buf[64];
		wsprintf(buf, TEXT("x = %d, y = %d"), xPOS, yPOS);	//ƴ���ַ���
		MessageBox(hwnd, buf, TEXT("����������λ��"), MB_OK);
		break;
	case WM_KEYDOWN:	//���¼���
		MessageBox(hwnd, TEXT("���̰���"), TEXT("���̰���"), MB_OK);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Hello World"), strlen("Hello World"));
		EndPaint(hwnd, &ps);
		break;
	}
	//����ֵ��Ĭ�ϴ���ʽ
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//���������


//WINAPI ����_stdcall �����Ĵ���˳�򣺴��ҵ���������ջ����������ǰ��ն�ջ
int WINAPI WinMain(
	HINSTANCE hInstance,	//Ӧ�ó���ʵ�����
	HINSTANCE hPervInstance,	//��һ��Ӧ�ó���������win32�����²���һ��Ϊnull ��������
	LPSTR lpCmdline,	//char * avgr[]
	int nShowCmd)	//��ʾ������ ��С�� ����
{
	//1.��ƴ���
	WNDCLASS wc;
	wc.cbClsExtra = 0;	//��Ķ����ڴ�
	wc.cbWndExtra = 0;	//���ڵĶ����ڴ�
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���ڱ���
	wc.hCursor = LoadCursor(NULL, IDC_HAND);	//���ù�꣬�����һ��ֵΪNULL������ʹ��ϵͳ�ṩ�Ĺ��
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);	//����ͼ�꣬�����һ��ֵΪNULL������Ŷʹ��ϵͳ�ṩ��ͼ��
	wc.hInstance = hInstance;	//Ӧ�ó���ʵ�����������WinMain�е��βμ���
	wc.lpfnWndProc = WindowProc;	//�ص����� ���ڹ���
	wc.lpszClassName = TEXT("�ײ㴰�ڵ�ʵ��");	//ָ������������
	wc.lpszMenuName = NULL;	//�˵�����
	wc.style = 0;	//��ʾ��� 0����Ĭ�Ϸ��

	//2.ע�ᴰ��
	RegisterClass(&wc);

	//3.��������
	/*
	lpClassName,	����
	lpWindowName,	������
	dwStyle,	��� ����WS_OVERLAPPEDWINDOW
	x,
	y,	��ʾ����
	nWidth,
	nHeight,	��� CW_USEDEFAULT Ĭ��ֵ
	hWndParent,	������ NULL
	hMenu,	�˵� NULL
	hInstance,	ʵ����� hInstance
	lpParam	����ֵ ��긽��ֵ NULL
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

	//4.��ʾ�����
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//5.ͨ��ѭ��ȡ��Ϣ
	/*
	HWND        hwnd;	�����ھ��
	UINT        message;	������Ϣ����
	WPARAM      wParam;	������Ϣ ������Ϣ
	LPARAM      lParam; ������Ϣ �����Ϣ ���Ҽ�
	DWORD       time;	��Ϣ����ʱ��
	POINT       pt;		������Ϣ �����Ϣ x y
	*/
	MSG msg;

	while (1)
	{
		/*
			_Out_ LPMSG lpMsg,	��װ�õ���Ϣָ��
			_In_opt_ HWND hWnd,	������Ϣ�Ĵ��� ��NULL���������д���
			_In_ UINT wMsgFilterMin,		��С�����Ĺ�����Ϣ��һ�����㣬���������е���Ϣ
			_In_ UINT wMsgFilterMax);
		*/
		if (GetMessage(&msg, NULL, 0, 0) == FALSE)
			break;
		//������Ϣ ������ϼ� ��ctrl+C
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
	}

	//6.�����ڹ���


	return 0;
}