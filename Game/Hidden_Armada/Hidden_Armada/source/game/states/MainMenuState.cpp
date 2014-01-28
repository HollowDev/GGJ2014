#include "MainMenuState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"
#include "../../engine/sound/SoundManager.h"
#include "GameplayState.h"
#include "../../engine/app/StateSystem.h"
#include "../../engine/app/WinApp.h"
#include "TestState.h"

#include "../../engine/input/InputController.h"

#include "../AssetManager.h"
#include "../ObjectFactory.h"
#include "../ObjectManager.h"

float lerp(float _start, float _end, float _percent)
{
	return (_start + _percent * (_end - _start));
}

MainMenuState::MainMenuState( void )
{
}

bool MainMenuState::Initialize( WinApp* _app )
{
	m_App = _app;
	isTitle = true;
	m_IsInvis = true;
	m_FlashTimer = 1.0f;
	m_Selected = PLAY_GAME;
	m_IsMoving = false;
	m_MoveTimer = 0.0f;
	m_MusicTimer = 0.0f;

	m_Input = new InputController();
	m_Input->Initialize(m_App->GetHWND(), m_App->GetHINSTANCE());

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
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 65;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 97;
	m_Buttons.push_back(newButton);

	// EXIT GAME
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255/4, 255, 255, 255);
	newButton->posX = (m_App->GetWidth() / 2) - (256 / 2);
	newButton->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 97;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 129;
	m_Buttons.push_back(newButton);

	// BACKGROUND
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255, 255, 255, 255);
	newButton->posX = 0;
	newButton->posY = 0;
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 0;
	newButton->sourceRect.right = 1024;	newButton->sourceRect.bottom = 768;
	m_Buttons.push_back(newButton);

	// PRESS START
	newButton = new spriteButtons();
	newButton->color = D3DCOLOR_ARGB(255, 255, 255, 255);
	newButton->posX = (m_App->GetWidth() / 2) - (256 / 2);
	newButton->posY = (m_App->GetHeight() / 2) + (33 / 2);
	newButton->sourceRect.left = 0;		newButton->sourceRect.top = 0;
	newButton->sourceRect.right = 256;	newButton->sourceRect.bottom = 33;
	m_Buttons.push_back(newButton);

	m_IntroMusic = SoundManager::GetInstance()->LoadMusic("assets/sounds/music/MainMenu_intro.mp3");
	m_MoveSFX = SoundManager::GetInstance()->LoadSFX("assets/sounds/sfx/menu_move.wav");
	m_MenuLoopMusic = SoundManager::GetInstance()->LoadMusic("assets/sounds/music/MainMenu_loop.mp3");
	SoundManager::GetInstance()->Play(m_IntroMusic, false, true);

	for(unsigned int i = 0; i < 2000; ++i)
	{
		D3DXVECTOR2 pos(rand()%1500-200,rand()%900-100);
		IEntity* explosion;
		ObjectFactory::GetInstance()->Create(&explosion,Entity_Explosion);
		if(rand()%2 == 0)
			((Explosion*)explosion)->Initialize(false);
		else if(rand()%50 != 0)
			((Explosion*)explosion)->Initialize(true);
		else
			((Explosion*)explosion)->Initialize(true,true);

		((Explosion*)explosion)->SetPos(D3DXVECTOR2(rand()%1500-200,rand()%900-100));
	}
	return true;
}

void MainMenuState::Release( void )
{
	ObjectManager::GetInstance()->Clear();
	ObjectFactory::GetInstance()->ProcessDestroy();
	SoundManager::GetInstance()->Pause(m_IntroMusic);
	SoundManager::GetInstance()->Pause(m_MenuLoopMusic);

	for(unsigned int i = 0; i < m_Buttons.size(); ++i)
	{
		delete m_Buttons[i];
	}

	//m_Input->Release();
	delete m_Input;
}

void MainMenuState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			TextureManager::GetInstance()->Draw(m_Background, m_Buttons[BACKGROUND]->posX, m_Buttons[BACKGROUND]->posY, 1.0f, 1.0f, &m_Buttons[BACKGROUND]->sourceRect);
			if(!isTitle)
			{
				TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[PLAY_GAME]->posX, m_Buttons[PLAY_GAME]->posY, 1.0f, 1.0f, &m_Buttons[PLAY_GAME]->sourceRect
													, 0.0f, 0.0f, 0.0f, m_Buttons[PLAY_GAME]->color);
				TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[OPTIONS]->posX, m_Buttons[OPTIONS]->posY, 1.0f, 1.0f, &m_Buttons[OPTIONS]->sourceRect
													, 0.0f, 0.0f, 0.0f, m_Buttons[OPTIONS]->color);
				TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[EXIT_GAME]->posX, m_Buttons[EXIT_GAME]->posY, 1.0f, 1.0f, &m_Buttons[EXIT_GAME]->sourceRect
													, 0.0f, 0.0f, 0.0f, m_Buttons[EXIT_GAME]->color);
			}
			else
				TextureManager::GetInstance()->Draw(m_TextImg, m_Buttons[PRESS_START]->posX, m_Buttons[PRESS_START]->posY, 1.0f, 1.0f, &m_Buttons[PRESS_START]->sourceRect
													, 0.0f, 0.0f, 0.0f, m_Buttons[PRESS_START]->color);
			
			ObjectManager::GetInstance()->Render(0,0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void MainMenuState::Update( float _dt )
{
	ObjectManager::GetInstance()->Update(_dt);
	ObjectFactory::GetInstance()->ProcessDestroy();

	m_Input->CheckInput(nullptr, this, nullptr);
	if(isTitle)
	{
		// Still on the title screen, blink the Press Start message
		m_FlashTimer += _dt;
		if(m_FlashTimer >= 1.0f)
		{
			m_IsInvis = !m_IsInvis;
			m_FlashTimer = 0.0f;
		}

		if(m_IsInvis)
			m_Buttons[PRESS_START]->color = D3DCOLOR_ARGB(0, 255, 255, 255);
		else 
			m_Buttons[PRESS_START]->color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	else
	{
		// On the main menu, track the options.
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
				}
				break;

			case OPTIONS:
				{
					m_Buttons[PLAY_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
					m_Buttons[PLAY_GAME]->color = D3DCOLOR_ARGB((int)lerp(255.0f, 255.0f / 4.0f, m_MoveTimer), 255, 255, 255);

					m_Buttons[OPTIONS]->posY = (m_App->GetHeight() / 2) + (33 / 2);
					m_Buttons[OPTIONS]->color = D3DCOLOR_ARGB((int)lerp(255/4, 255.0f, m_MoveTimer), 255, 255, 255);

					m_Buttons[EXIT_GAME]->posY = (m_App->GetHeight() / 2) + (33 / 2) + 50;
					m_Buttons[EXIT_GAME]->color = D3DCOLOR_ARGB((int)lerp(0, 255.0f / 4, m_MoveTimer), 255, 255, 255);
				}
				break;

			case EXIT_GAME:
				{
					m_Buttons[OPTIONS]->posY = (m_App->GetHeight() / 2) + (33 / 2) - 50;
					m_Buttons[OPTIONS]->color = D3DCOLOR_ARGB((int)lerp(255.0f, 255.0f / 4.0f, m_MoveTimer), 255, 255, 255);

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

	m_MusicTimer += _dt;
	if(m_MusicTimer > 8.57f)
	{
		SoundManager::GetInstance()->Play(m_MenuLoopMusic, true, false);
	}
}

bool MainMenuState::Input( void )
{
	/*if(GetAsyncKeyState(VK_ESCAPE))
	{
		m_Selected = EXIT_GAME;
		m_IsMoving = true;
		m_MoveTimer = 0.0f;
		SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
		while(GetAsyncKeyState(VK_ESCAPE));
	}*/

	if(m_Input->Input_Cancel())
	{
		m_Selected = EXIT_GAME;
		m_IsMoving = true;
		m_MoveTimer = 0.0f;
		SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
	}

	if(isTitle)
	{
		/*if(GetAsyncKeyState(VK_RETURN))
		{
		isTitle = false;
		while(GetAsyncKeyState(VK_RETURN));
		}*/
		if(m_Input->Input_StartPressed())
		{
			isTitle = false;
		}
	}
	else
	{
		if(m_Input->Input_Confirm())//GetAsyncKeyState(VK_RETURN))
		{
			switch(m_Selected)
			{
			case PLAY_GAME:
				StateSystem::GetInstance()->ChangeState(new GameplayState());
				break;

			case OPTIONS:
				//StateSystem::GetInstance()->AddState(new OptionsState());
				break;

			case EXIT_GAME:
				return false;
			};

			//while(GetAsyncKeyState(VK_RETURN));
		}

		if(m_Input->Input_DownDown())//GetAsyncKeyState(VK_DOWN))
		{
			m_Selected++;
			if(m_Selected > 2)
				m_Selected = 0;
			m_IsMoving = true;
			m_MoveTimer = 0.0f;
			SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
			//while(m_Input->Input_DownDown());
		}

		if(m_Input->Input_UpDown())//GetAsyncKeyState(VK_UP))
		{
			m_Selected--;
			if(m_Selected < 0)
				m_Selected = 2;
			m_IsMoving = true;
			m_MoveTimer = 0.0f;
			SoundManager::GetInstance()->Play(m_MoveSFX, false, false);
			//while(m_Input->Input_UpDown());
		}
	}

	return true;
}
