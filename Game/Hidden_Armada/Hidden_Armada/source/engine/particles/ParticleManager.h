#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include <list>

class Emitter;

class ParticleManager
{
private:
	typedef std::list<Emitter*> EmitterList;
	EmitterList m_Emitters;

public:
	ParticleManager(void);
	~ParticleManager(void);

	void Update(float _dt);
	void Render(void);

	Emitter* AddEmitter(const int _maxParticles, const float _x, const float _y,
						const float _lifetime, const float _radius,  int _textureID);
	void RemoveEmitter(Emitter& _emitterToRemove);
};

#endif