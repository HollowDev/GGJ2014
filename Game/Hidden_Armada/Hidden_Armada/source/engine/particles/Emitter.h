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

	float m_PosX;
	float m_PosY;
	float m_SpawnRate;
	float m_SpawnTimer;

	void AddParticle(void);

	Emitter(void);
public:
	Emitter(
		const int _maxParticles,
		const float _x, const float _y,
		const float _lifetime,
		const float _spawnradius,
		int _textureID);
	~Emitter(void);

	void Update(float _dt);
	void Render(void);

	void SetPosition(const float _x, const float _y);
	void GetPosition(const float _x, const float _y);
};

#endif