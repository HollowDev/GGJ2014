#include "StateSystem.h"
#include "BaseState.h"
#include "WinApp.h"

#include "../memory_macros.h"

StateSystem StateSystem::m_Instance;

void StateSystem::Initialize( WinApp* _winApp, BaseState* _state )
{
	m_App = _winApp;

	_state->Initialize(m_App);
	m_States.push_back(_state);
}

void StateSystem::Release( void )
{
	for(unsigned int i = 0; i < m_States.size(); ++i)
		SAFE_DELETE( m_States[i] );
	m_States.clear();

	for(unsigned int i = 0; i < m_AddStates.size(); ++i)
		SAFE_DELETE( m_AddStates[i] );
	m_AddStates.clear();

	for(unsigned int i = 0; i < m_RemoveStates.size(); ++i)
		SAFE_DELETE( m_RemoveStates[i] );
	m_RemoveStates.clear();

	SAFE_DELETE(m_ChangeState);
}

void StateSystem::Render( void )
{
	for(unsigned int i = 0; i < m_States.size(); ++i)
		m_States[i]->Render();
}

void StateSystem::Update( float _dt )
{
	for(unsigned int i = 0; i < m_States.size(); ++i)
		m_States[i]->Update(_dt);

	// Update states that need to change, be removed, be added
	CheckChanges();
}

void StateSystem::CheckChanges( void )
{
	if(m_ChangeState != nullptr)
	{
		for(unsigned int i = 0; i < m_States.size(); ++i)
			SAFE_DELETE(m_States[i]);
		m_States.clear();
		m_ChangeState->Initialize(m_App);
		m_States.push_back(m_ChangeState);
		m_ChangeState = nullptr;
	}
	else if(m_AddStates.size() > 0)
	{
		for(unsigned int i = 0; i < m_AddStates.size(); ++i)
		{
			m_AddStates[i]->Initialize(m_App);
			m_States.push_back(m_AddStates[i]);
		}
		m_AddStates.clear();
	}
	else if(m_RemoveStates.size() > 0)
	{
		for(unsigned int i = 0; i < m_RemoveStates.size(); ++i)
		{
			for(unsigned int j = 0; j < m_States.size(); ++j)
			{
				if(m_States[j] == m_RemoveStates[i])
				{
					m_States.erase(m_States.begin()+j);
					j--;
				}
			}
		}
		m_RemoveStates.clear();
	}
}

bool StateSystem::Input( void )
{
	bool active = true;
	for(unsigned int i = 0; i < m_States.size(); ++i)
		if(!m_States[i]->Input())
			active = false;

	return active;
}

void StateSystem::AddState( BaseState* _state )
{
	m_AddStates.push_back(_state);
}

void StateSystem::RemoveState( BaseState* _state )
{
	m_RemoveStates.push_back(_state);
}

void StateSystem::ChangeState( BaseState* _state )
{
	m_ChangeState = _state;
}
