#include "Emitter.h"
#include "Particle.h"

#include "../memory_macros.h"

Emitter::Emitter( const int _maxParticles, float _vX, float _vY, const float _x, const float _y,
					const float _lifetime, const float _spawnradius, int _textureID )
{
	m_CurrentParticles = 0;
	m_MaxParticles = _maxParticles;
	m_Particles = new Particle[m_MaxParticles];
	m_Lifetime = _lifetime;
	m_SpawnRadius = _spawnradius;
	m_VelX = _vX;
	m_VelY = _vY;
	m_PosX = _x;
	m_PosY = _y;
	m_SpawnRate = 0.05f; // _spawnRate;
	m_SpawnTimer = m_SpawnRate;
	m_ImgID =  _textureID;
}

Emitter::~Emitter( void )
{
	delete[] m_Particles;
}

void Emitter::Update(float _dt, float _x, float _y)
{
	Particle temp;

	m_PosX = _x + m_VelX * _dt;
	m_PosY = _y + m_VelY * _dt;
	m_SpawnTimer += _dt;
	if(m_CurrentParticles < m_MaxParticles)
	{
		if(m_SpawnTimer >= m_SpawnRate)
		{
			AddParticle(_x, _y);
			m_SpawnTimer = 0.0f;
		}
	}

	for(int i = 0; i < m_CurrentParticles; ++i)
	{
		if(m_Particles[i].m_Lifetime > 0.0f)
			m_Particles[i].Update(_dt);
		else
		{
			if(m_CurrentParticles > 1)
			{
				temp = m_Particles[i];
				m_Particles[i] = m_Particles[m_CurrentParticles - 1];
			}
			--m_CurrentParticles;
		}
	}
}

void Emitter::Render(int _x, int _y)
{
	for(int i = 0; i < m_CurrentParticles; ++i)
	{
		if(m_Particles[i].m_Lifetime > 0.0f)
			m_Particles[i].Render(_x, _y);
	}
}

void Emitter::AddParticle(float _x, float _y)
{
	if(m_CurrentParticles <= m_MaxParticles - 1)
	{
		Particle* newParticle = &m_Particles[m_CurrentParticles];
		newParticle->m_PosX = m_PosX;
		newParticle->m_PosY = m_PosY;
		newParticle->m_VelX = m_VelX;
		newParticle->m_VelY = m_VelY;
		newParticle->m_Lifetime = m_Lifetime;
		newParticle->m_Color;
		newParticle->m_ImgID = m_ImgID;
		++m_CurrentParticles;
	}
}