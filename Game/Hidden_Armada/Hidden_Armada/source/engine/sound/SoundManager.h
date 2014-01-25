#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "../../../../Lib/fmod/inc/fmod.hpp"
#include "../../../../Lib/fmod/inc/fmod_errors.h"
#include <tchar.h>
#include <vector>

bool FMODErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		return false;
	}
	return true;
}

class SoundManager
{
private:
	FMOD::System*		m_System;
	FMOD_SPEAKERMODE	m_SpeakerMode;
	FMOD_CAPS			m_Caps;

	FMOD::ChannelGroup*	m_ChannelMusic;
	FMOD::ChannelGroup*	m_ChannelSFX;

	std::vector<FMOD::Sound*> m_Music;
	std::vector<FMOD::Sound*> m_SFX;

public:
	SoundManager(void);
	~SoundManager(void);

	bool Initialize(void);
	void Release(void);
	int LoadMusic(const TCHAR* _fileName);
	int LoadSFX(const TCHAR* _fileName);
	void UnloadMusic(int _musicID);
	void UnloadSFX(int _sfxID);

	void PlayMusic(int _musicID, bool _isLooping);
	void StopMusic(int _musicID);
	void PlaySFX(int _sfxID, bool _isLooping);
	void StopSFX(int _sfxID);
};

#endif