#ifndef _OPTIONS_STATE_H_
#define _OPTIONS_STATE_H_

#include "../../engine/app/BaseState.h"
#include <vector>

class OptionsState : public BaseState
{
private:
	std::vector<spriteButtons*> m_Buttons;

public:
	OptionsState( void );
	~OptionsState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif