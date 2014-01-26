#include "Particle.h"

#include "../renderer/TextureManager.h"


Particle::Particle( void )
{
}

Particle::~Particle( void )
{

}

void Particle::Update(float _dt)
{
	// Decrease the particle's life
	m_Lifetime -= _dt;
	
	// Update the particle's position
	m_PosX += m_VelX * _dt;
	m_PosY += m_VelY * _dt;

	// Update the color (if having to alter the color)
	float alpha = lerp(0.0f, 255.0f, m_Lifetime/m_MaxLife);
	m_Color = D3DCOLOR_ARGB(int(alpha), 255, 255, 255);

	// Update the size (if scaling over time)
}

void Particle::Render(int _x, int _y)
{
	if(m_Lifetime > 0.0f)
		TextureManager::GetInstance()->Draw(m_ImgID, (int)m_PosX + _x, (int)m_PosY + _y,
											1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, m_Color);
}