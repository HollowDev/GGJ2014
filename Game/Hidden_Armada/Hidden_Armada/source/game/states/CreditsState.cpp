#include "CreditsState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"
#include "../../engine/app/StateSystem.h"
#include "MainMenuState.h"
#include "../../engine/input/InputController.h"
#include "../../engine/app/WinApp.h"

CreditsState::CreditsState( void )
{

}

bool CreditsState::Initialize( WinApp* _app )
{
	m_App = _app;

	m_Timer = 0.0f;

	m_Input = new InputController();
	m_Input->Initialize(m_App->GetHWND(), m_App->GetHINSTANCE());

	m_Img = AssetManager::GetInstance()->GetAsset(Asset_Credits);

	return true;
}

void CreditsState::Release( void )
{

}

void CreditsState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			TextureManager::GetInstance()->Draw(m_Img, 0, 0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void CreditsState::Update( float _dt )
{
	m_Timer += _dt;
	m_Input->CheckInput(nullptr, this, nullptr);
	if(m_Timer > 5.0f)
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
}

bool CreditsState::Input( void )
{
	if(m_Input->Input_Confirm() || m_Input->Input_Cancel())
		m_Timer = 5.0f;
	return true;
}
