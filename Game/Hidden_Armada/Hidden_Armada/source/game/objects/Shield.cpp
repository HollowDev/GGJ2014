#include "Shield.h"

Shield::Shield(void)
{
	m_Render = false;
	m_RenderTimer = 2.0f;
}

Shield::~Shield(void)
{

}

void Shield::Update(float _dt)
{
	BaseEntity::Update(_dt);

	if(m_CurrShield == 0.0f)
	{
		m_Render = false;
		m_RenderTimer = 2.0f;
	}

	if(m_RenderTimer != 2.0f)
		m_RenderTimer += _dt;

	if(m_RenderTimer > 2.0f)
	{
		m_RenderTimer = 2.0f;
		m_Render = false;
	}
}

void Shield::Render( int _x, int _y )
{
	if(m_Render)
		BaseEntity::Render(_x, _y);
}