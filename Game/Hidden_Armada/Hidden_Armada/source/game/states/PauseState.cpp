#include "PauseState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"
#include "../../game/AssetManager.h"
#include "../../engine/app/WinApp.h"
#include "../../engine/sound/SoundManager.h"
#include "../../engine/input/InputController.h"
#include "../../engine/app/StateSystem.h"

PauseState::PauseState( InputController* _input, bool& _gamePaused, bool& _quitGame  )
{
	m_Input = _input;
	m_Paused = &_gamePaused;
	m_QuitGame = &_quitGame;
}

bool PauseState::Initialize( WinApp* _app )
{
	m_App = _app;
	m_IsMoving = false;
	m_MoveTimer = 0.0f;

	m_Selected = PLAY_GAME;

	// Load Textures
	m_Background = AssetManager::GetInstance()->GetAsset(Asset_MainTitle);//TextureManager::GetInstance()->LoadTexture(L"assets/textures/mainmenu_background.png");
	m_TextImg = AssetManager::GetInstance()->GetAsset(Asset_TitleLabels);//TextureManager::GetInstance()->LoadTexture(L"assets/textures/mainmenu_options_text.png");

	// PLAY GAME
	spriteButtons* newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255, 255, 255, 255);
	newButton->posX = (m_App->GetWidth() / 2) - (256 / 2);
	newButton->posY = (m_App->GetHeight() / 2) + (33 / 2);
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 33;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 66;
	m_Buttons.push_back(newButton);

	// OPTIONS
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255/4, 255, 255, 255);
	newButton->posX = (m_App->GetWidth() / 2) - (256 / 2);
	newButton->posY = (m_App->GetHeight() / 2) + (33 / 2) + 50;
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 33;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 66;
	m_Buttons.push_back(newButton);

	// EXIT GAME
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255/4, 255, 255, 255);
	newButton->posX = (m_App->GetWidth() / 2) - (256 / 2);
	newButton->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 97;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 129;
	m_Buttons.push_back(newButton);

	m_Buttons[OPTIONS]->sourceRect = m_Buttons[EXIT_GAME]->sourceRect;

	// BACKGROUND
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255, 255, 255, 255);
	newButton->posX = 0;
	newButton->posY = 0;
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 0;
	newButton->sourceRect.right = 1024;	newButton->sourceRect.bottom = 768;
	m_Buttons.push_back(newButton);

	m_MoveSFX = SoundManager::GetInstance()->LoadSFX("assets/sounds/sfx/menu_move.wav");

	return true;
}

void PauseState::Release( void )
{
	for(unsigned int i = 0; i < m_Buttons.size(); ++i)
	{
		delete m_Buttons[i];
	}
}

void PauseState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			TextureManager::GetInstance()->Draw(m_Background, m_Buttons[BACKGROUND]->posX, m_Buttons[BACKGROUND]->posY, 1.0f, 1.0f, &m_Buttons[BACKGROUND]->sourceRect);

			TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[PLAY_GAME]->posX, m_Buttons[PLAY_GAME]->posY, 1.0f, 1.0f, &m_Buttons[PLAY_GAME]->sourceRect
				, 0.0f, 0.0f, 0.0f, m_Buttons[PLAY_GAME]->color);

			TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[OPTIONS]->posX, m_Buttons[OPTIONS]->posY, 1.0f, 1.0f, &m_Buttons[OPTIONS]->sourceRect
				, 0.0f, 0.0f, 0.0f, m_Buttons[OPTIONS]->color);

			TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[EXIT_GAME]->posX, m_Buttons[EXIT_GAME]->posY, 1.0f, 1.0f, &m_Buttons[EXIT_GAME]->sourceRect
				, 0.0f, 0.0f, 0.0f, m_Buttons[EXIT_GAME]->color);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void PauseState::Update( float _dt )
{
	m_Input->CheckInput(nullptr, this, nullptr);
	if(m_IsMoving)
	{
		// options are moving and changing alpha
		switch(m_Selected)
		{
		case PLAY_GAME:
			{
				m_Buttons[EXIT_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
				m_Buttons[EXIT_GAME]->color = D3DCOLOR_ARGB((int)lerp(255.0f, 255.0f / 4.0f, m_MoveTimer), 255, 255, 255);

				m_Buttons[PLAY_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2);
				m_Buttons[PLAY_GAME]->color = D3DCOLOR_ARGB((int)lerp(255/4, 255.0f, m_MoveTimer), 255, 255, 255);

				m_Buttons[OPTIONS]->posY = (m_App->GetHeight() / 2) + (33 / 2) + 50;
				m_Buttons[OPTIONS]->color = D3DCOLOR_ARGB((int)lerp(0.0f, 255.0f / 4.0f, m_MoveTimer), 255, 255, 255);
				m_Buttons[OPTIONS]->sourceRect = m_Buttons[EXIT_GAME]->sourceRect;

			}
			break;

		case EXIT_GAME:
			{
				m_Buttons[OPTIONS]->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
				m_Buttons[OPTIONS]->color = D3DCOLOR_ARGB((int)lerp(255.0f, 255.0f / 4.0f, m_MoveTimer), 255, 255, 255);
				m_Buttons[OPTIONS]->sourceRect = m_Buttons[PLAY_GAME]->sourceRect;

				m_Buttons[EXIT_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2);
				m_Buttons[EXIT_GAME]->color = D3DCOLOR_ARGB((int)lerp(255/4, 255.0f, m_MoveTimer), 255, 255, 255);

				m_Buttons[PLAY_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2) + 50;
				m_Buttons[PLAY_GAME]->color = D3DCOLOR_ARGB((int)lerp(0, 255.0f / 4, m_MoveTimer), 255, 255, 255);
			}
			break;
		}

		m_MoveTimer += _dt;
		if(m_MoveTimer > 1.0f)
		{
			m_IsMoving = false;
			m_MoveTimer = 0.0f;
		}
	}
}

bool PauseState::Input( void )
{
	if(m_Input->Input_Confirm())//GetAsyncKeyState(VK_RETURN))
	{
		switch(m_Selected)
		{
		case PLAY_GAME:
			StateSystem::GetInstance()->RemoveState(this);
			(*m_Paused) = false;
			return true;
			break;

		case OPTIONS:
			break;

		case EXIT_GAME:
			StateSystem::GetInstance()->RemoveState(this);
			(*m_Paused) = true;
			(*m_QuitGame) = true;
			return true;
			break;
		};
	}

	if(m_Input->Input_DownDown())
	{
		m_Selected--;
		if(m_Selected < 0)
			m_Selected = 2;

		if(m_Selected == 1)
			m_Selected = 0;
		m_IsMoving = true;
		m_MoveTimer = 0.0f;
		SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
	}

	if(m_Input->Input_UpDown())
	{
		m_Selected++;
		if(m_Selected > 2)
			m_Selected = 0;

		if(m_Selected == 1)
			m_Selected = 2;
		m_IsMoving = true;
		m_MoveTimer = 0.0f;
		SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
	}

	return true;
}
