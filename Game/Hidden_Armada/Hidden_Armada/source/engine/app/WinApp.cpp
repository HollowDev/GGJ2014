#include "WinApp.h"
#include "BaseState.h"
#include "StateSystem.h"
#include "Timer.h"
#include "../renderer/D3D9Handler.h"
#include "../renderer/TextureManager.h"
#include "../memory_macros.h"

WinApp::WinApp( void )
{
	m_HWND = NULL;
	m_HInstance = NULL;
	m_Active = false;
	m_WindowWidth = -1;
	m_WindowHeight = -1;
	m_IsClosing = false;
}

void WinApp::Initialize( LPCWSTR _title, HINSTANCE _HInstance, BaseState* _startState, 
	int _width, int _height, bool _windowed )
{
	m_HInstance = _HInstance;
	m_WindowWidth = _width;
	m_WindowHeight = _height;
	m_Active = true;

	// Define the window
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WinApp::StaticWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_HInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= _title;
	wcex.hIconSm		= 0;

	// Reguster the window
	RegisterClassEx(&wcex);

	// Create the window
	m_HWND = CreateWindow(_title, _title, (_windowed ? WS_OVERLAPPEDWINDOW : WS_EX_TOPMOST), CW_USEDEFAULT,
		0, m_WindowWidth, m_WindowHeight, 0, 0, m_HInstance, this);

	// Adjust to desired size
	RECT rect = {0, 0, m_WindowWidth, m_WindowHeight};
	AdjustWindowRect(&rect, GetWindowLong(m_HWND, GWL_STYLE), FALSE);
	SetWindowPos(m_HWND, HWND_TOP, 0, 0, rect.right-rect.left, rect.bottom-rect.top,
				 SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);

	// Save current location/size
	ZeroMemory(&m_WP, sizeof(WINDOWPLACEMENT));
	m_WP.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(m_HWND, &m_WP);

	// TODO:: Initialize handlers
	D3D9Handler::Initialize(m_HWND, _windowed);
	TextureManager::GetInstance()->Initialize(D3D9Handler::m_Device, D3D9Handler::m_Sprite);
	StateSystem::GetInstance()->Initialize(this,_startState);
	m_StateSystem = StateSystem::GetInstance();

	m_Timer = new Timer();
	m_Timer->Init();
	m_Timer->Reset();
}

void WinApp::Release( void )
{
	m_IsClosing = true;
	
	SAFE_DELETE(m_Timer);
	SAFE_DELETE(m_StateSystem);
}

void WinApp::Run( void )
{
	MSG msg;
	while(m_Active)
	{
		// Did we recieve a message, or are we idling?
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Advance Game Frame
			this->Update();
			this->Render();
		}
	}
}

void WinApp::Update( void )
{
	m_Timer->Update();

	float deltaTime = m_Timer->GetDeltaTime();
	if(deltaTime > 0.125f)
		deltaTime = 0.125f;
	
	// Update input
	if(!m_StateSystem->Input())
		m_Active = false;
	// Update state
	m_StateSystem->Update(deltaTime);
}

void WinApp::Render( void )
{
	if( !m_Active )
		return;

	m_StateSystem->Render();
}

LRESULT CALLBACK WinApp::StaticWndProc( HWND _hWnd, UINT _message, 
	WPARAM _wParam, LPARAM _lParam )
{
	if(_message == WM_CREATE)
        SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)_lParam)->lpCreateParams);

    WinApp *targetApp = (WinApp*)GetWindowLongPtr(_hWnd,GWLP_USERDATA);

    if(targetApp)
        return targetApp->WndProc(_hWnd, _message, _wParam, _lParam);

    return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

LRESULT CALLBACK WinApp::WndProc( HWND _hWnd, UINT _message, 
	WPARAM _wParam, LPARAM _lParam )
{
	switch(_message)
	{
	case WM_DESTROY:
		{
			m_Active = false;
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		{
			ValidateRect(_hWnd, 0);
		}
		break;
	}
	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}
