#include "TestState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

#include "../ObjectFactory.h"
#include "../ObjectManager.h"
#include "../AssetManager.h"

TestState::TestState( void )
{

}

bool TestState::Initialize( WinApp* _app )
{
	m_App = _app;

	for(unsigned int i = 0; i < 50; ++i)
	{
		int posX = rand()%1024;
		int posY = rand()%768;
		IEntity* asteroid;
		ObjectFactory::GetInstance()->Create(&asteroid,Entity_Asteroid);
		((BaseEntity*)asteroid)->SetPos(D3DXVECTOR2(float(posX),float(posY)));
		((BaseEntity*)asteroid)->SetSize(16);
		((BaseEntity*)asteroid)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_Asteroid04));
	}

	ObjectManager::GetInstance()->InitQuadtree(5,25);

	return true;
}

void TestState::Release( void )
{
	ObjectManager::GetInstance()->Clear();
	ObjectFactory::GetInstance()->ProcessDestroy();
}

void TestState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			ObjectManager::GetInstance()->Render(0,0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void TestState::Update( float _dt )
{
	ObjectManager::GetInstance()->Update(_dt);
	ObjectManager::GetInstance()->CheckCollision();
	ObjectFactory::GetInstance()->ProcessDestroy();
}

bool TestState::Input( void )
{
	return true;
}
