#include "ParticleManager.h"
#include "../memory_macros.h"
#include "Emitter.h"


ParticleManager::ParticleManager( void )
{

}

ParticleManager::~ParticleManager( void )
{
	for(EmitterList::iterator i = m_Emitters.begin(); i != m_Emitters.end(); ++i)
		SAFE_DELETE((*i));
	m_Emitters.clear();
}

void ParticleManager::Update( float _dt )
{
	for(EmitterList::iterator i = m_Emitters.begin(); i != m_Emitters.end(); ++i)
	{
		Emitter& emitter = **i;
		emitter.Update(_dt);
	}
}

void ParticleManager::Render( void )
{
	for(EmitterList::iterator i = m_Emitters.begin(); i != m_Emitters.end(); ++i)
	{
		Emitter& emitter = **i;
		emitter.Render();
	}
}

Emitter* ParticleManager::AddEmitter( const int _maxParticles, const float _x, const float _y, const float _lifetime, const float _radius, int _textureID )
{
	if(_maxParticles <= 0)
		return nullptr;

	Emitter* newEmitter = new Emitter(_maxParticles, _x, _y, _lifetime, _radius, _textureID);
	m_Emitters.push_back(newEmitter);
	return newEmitter;
}

void ParticleManager::RemoveEmitter( Emitter& _emitterToRemove )
{
	EmitterList::iterator i = std::find(m_Emitters.begin(), m_Emitters.end(), &_emitterToRemove);
	if(i != m_Emitters.end())
		SAFE_DELETE((*i));
}