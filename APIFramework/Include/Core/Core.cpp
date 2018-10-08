#include "Core.h"
#include "Timer.h"
#include "../Scene/SceneManager.h"

DEFINITION_SINGLE(Core);
bool Core::m_bLoop = true;
Core::Core() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();
}


Core::~Core()
{
	DESTROY_SINGLE(Timer);
	DESTROY_SINGLE(SceneManager);
}

bool Core::Init(HINSTANCE hInst)
{
	this->m_hInst = hInst;

	MyRegisterClass();

	//Resolution
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();

	m_hDc = GetDC(m_hWnd);
	if (!GET_SINGLE(Timer)->Init())
		return false;

	//Scene
	if (!GET_SINGLE(SceneManager)->Init())
		return false;
	
	return true;
}

int Core::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (!PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
		}

	}
	return (int)msg.wParam;
}

void Core::Logic()
{
	GET_SINGLE(Timer)->Update();

	float fDeltaTime = GET_SINGLE(Timer)->GetDeltaTime();
	
	Input(fDeltaTime);
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void Core::Input(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->Input(fDeltaTime);
}

int Core::Update(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->Update(fDeltaTime);

	return 0;
}

int Core::LateUpdate(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->LateUpdate(fDeltaTime);

	return 0;
}

void Core::Collision(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->Collision(fDeltaTime);

}

void Core::Render(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->Render(m_hDc,fDeltaTime);

}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEXW);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"YSAPI";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

BOOL Core::Create()
{
	m_hWnd = CreateWindowW(L"YSAPI", L"YSAPI",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	RECT rc = { 0,0, m_tRS.iW, m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	
	return TRUE;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
