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

	void SetPosition(const float _x, const float _y);
	void GetPosition(const float _x, const float _y);
};

#endif