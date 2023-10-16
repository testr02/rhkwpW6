#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>


#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("tlqkf");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201807058정의찬"),
		// WS_OVERLAPPEDWINDOW 를 사용하면
		// WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION 를 사용한 것과 같은 효과
		WS_OVERLAPPEDWINDOW,
		0, 0,
		//width와 height
		800, 600,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL) {
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트 해야 보임.

	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		// 메시지 처리
		if (GetMessage(&msg, hwnd, 0, 0)) {
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))

			//메시지 해석
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달
			DispatchMessage(&msg);
		}
	}
	//프로그램 종료
	return (int)msg.wParam;
}