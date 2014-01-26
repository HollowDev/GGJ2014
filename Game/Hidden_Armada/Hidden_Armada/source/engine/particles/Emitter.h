#ifndef _EMITTER_H_
#define _EMITTER_H_

class Particle;

class Emitter
{
private:
	int m_CurrentParticles;
	int m_MaxParticles;
	Particle* m_Particles;
	float m_Lifetime;
	float m_SpawnRadius;
	int m_ImgID;

	float m_VelX, m_VelY;
	float m_PosX;
	float m_PosY;
	float m_SpawnRate;
	float m_SpawnTimer;

	void AddParticle(float _x, float _y);

	Emitter(void);
public:
	Emitter(
		const int _maxParticles,
		float _vX, float _vY,
		const float _x, const float _y,
		const float _lifetime,
		const float _spawnradius,
		int _textureID);
	~Emitter(void);

	void Update(float _dt, float _x, float _y);
	void Render(int _x, int _y);

	void SetPosition(float _x, float _y) { m_PosX = _x; m_PosY = _y; }
	void SetVelocity(float _x, float _y) { m_VelX = _x; m_VelY = _y; }
	void GetPosition(float& _x, float& _y) { _x = m_PosX; _y = m_PosY; }
	void GetVelocity(float& _x, float& _y) { _x = m_VelX; _y = m_VelY; }
};

#endif