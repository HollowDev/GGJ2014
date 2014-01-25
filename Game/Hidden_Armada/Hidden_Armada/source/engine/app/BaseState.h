#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

class WinApp;
class BaseState
{
protected:
	WinApp* m_App;
public:
	virtual ~BaseState( void ) = 0 {}

	virtual bool Initialize( WinApp* _app ) = 0;
	virtual void Release( void ) = 0;
	
	virtual void Render( void ) = 0;
	virtual void Update( float _dt ) = 0;
	virtual bool Input( void ) = 0;
};

#endif