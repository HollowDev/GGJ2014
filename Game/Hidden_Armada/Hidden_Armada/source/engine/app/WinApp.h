#ifndef _WIN_APP_H_
#define _WIN_APP_H_

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		    
#define DIRECTINPUT_VERSION 0x0800

// Windows Header Files:
#include <windows.h>

class BaseState;
class StateSystem;
class WinApp
{
	HWND			m_HWND;
	HINSTANCE		m_HInstance;
	bool			m_Active;
	int				m_WindowWidth;
	int				m_WindowHeight;
	WINDOWPLACEMENT	m_WP;
	bool			m_IsClosing;

	StateSystem*	m_StateSystem;

	LRESULT CALLBACK WndProc( HWND _hWnd, UINT _message, 
		WPARAM _wParam, LPARAM _lParam );

	void Update( void );
	void Render( void );
public:
	WinApp( void );
	~WinApp( void ) { Release(); }

	void Initialize( LPCWSTR _title, HINSTANCE _HInstance, BaseState* _startState,
		int _width, int _height, bool _windowed = true);
	void Release( void );

	void Run( void );

	static LRESULT CALLBACK StaticWndProc( HWND _hWnd, UINT _message, 
		WPARAM _wParam, LPARAM _lParam );

	inline int GetWidth( void ) const { return m_WindowWidth; }
	inline int GetHeight( void ) const { return m_WindowHeight; }
	inline HWND GetHWND( void ) const { return m_HWND; }
};

#endif