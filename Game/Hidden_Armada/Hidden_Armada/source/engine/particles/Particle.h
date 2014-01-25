#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "../windows.h"

class Particle
{
private:
	float		m_PosX;
	float		m_PosY;
	float		m_MaxVelocity;
	DWORD		m_Color;
	float		m_VelX;
	float		m_VelY;
	float		m_Lifetime;
	int			m_ImgID;

	friend class Emitter;
	Particle(void);

public:
	~Particle(void);

	Particle& operator=(const Particle& rhs)
	{
		m_PosX = rhs.m_PosX;
		m_PosY = rhs.m_PosY;
		m_MaxVelocity = rhs.m_MaxVelocity;
		m_Color = rhs.m_Color;
		m_VelX = rhs.m_VelX;
		m_VelY = rhs.m_VelY;
		//m_Size = rhs.m_Size;
		m_Lifetime = rhs.m_Lifetime;
		m_ImgID = rhs.m_ImgID;
		return *this;
	}

	void Update(float _dt);
	void Render(void);
};

#endif