#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "../../../../Lib/fmod/inc/fmod.hpp"
#include "../../../../Lib/fmod/inc/fmod_errors.h"
#include "../../engine/memory_macros.h"
#include <tchar.h>
#include <vector>

struct Sounds
{
	bool			isSFX;
	FMOD::Sound*	sound;
	FMOD::Channel*	channel;
	char*			filename;
};

class SoundManager
{
private:
	FMOD::System*		m_System;
	FMOD_SPEAKERMODE	m_SpeakerMode;
	FMOD_CAPS			m_Caps;

	FMOD::ChannelGroup*	m_ChannelMusic;
	FMOD::ChannelGroup*	m_ChannelSFX;

	std::vector<Sounds*> m_Sounds;

	int m_CurrSounds;

	static SoundManager m_Instance;

	bool inline FMODCheckError(FMOD_RESULT _result)
	{
		if(_result != FMOD_OK)
		{
			return false;
		}
		return true;
	}

public:
	SoundManager(void);
	~SoundManager(void);

	static SoundManager* GetInstance(void) { return &m_Instance; }

	bool Initialize(void);
	void Release(void);

	void Update(void);

	int LoadMusic(const char* _fileName);
	int LoadSFX(const char* _fileName);

	void Play(int _soundID, bool _isLooping);
	void PauseAllMusic();
	void UnpauseAllMusic();
	void PauseAllSFX();
	void UnpauseAllSFX();
	void Pause(int _soundID);
	void Unpause(int _soundID);

	bool IsPlaying(int _soundID);
};

#endif