#ifndef _STATE_SYSTEM_H_
#define _STATE_SYSTEM_H_

#include <vector>
using std::vector;

class BaseState;
class WinApp;
class StateSystem
{
	WinApp* m_App;
	vector<BaseState*> m_States;

	vector<BaseState*> m_AddStates;
	vector<BaseState*> m_RemoveStates;
	BaseState* m_ChangeState;

	static StateSystem m_Instance;

	void CheckChanges( void );

public:
	~StateSystem( void ) { Release(); }
	static StateSystem* GetInstance( void ) { return &m_Instance; }
	
	void Initialize( WinApp* _winApp, BaseState* _state );
	void Release( void );

	void Render( void );
	void Update( float _dt );
	bool Input( void );

	void AddState( BaseState* _state );
	void RemoveState( BaseState* _state );
	void ChangeState( BaseState* _state );

};


#endif