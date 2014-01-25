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

	// Update the size (if scaling over time)
}

void Particle::Render(void)
{
	if(m_Lifetime > 0.0f)
		TextureManager::GetInstance()->Draw(m_ImgID, (int)m_PosX, (int)m_PosY,
											1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, m_Color);
}