#include "SoundManager.h"

#include <string.h>

SoundManager SoundManager::m_Instance;

SoundManager::SoundManager(void)
{

}

SoundManager::~SoundManager(void)
{

}

bool SoundManager::Initialize( void )
{
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	char name[256];

	m_CurrSounds = 0;

	result = FMOD::System_Create(&m_System);
	if(!FMODCheckError(result))
		return false;

	result = m_System->getVersion(&version);
	if(!FMODCheckError(result))
		return false;

	if(version < FMOD_VERSION)
		return false;

	result = m_System->getNumDrivers(&numDrivers);
	if(!FMODCheckError(result))
		return false;

	// No sound cards (disable sound)
	if(numDrivers == 0)
	{
		result = m_System->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if(!FMODCheckError(result))
			return false;
	}
	// At least one sound card
	else
	{
		result = m_System->getDriverCaps(0, &m_Caps, 0, &m_SpeakerMode);
		if(!FMODCheckError(result))
			return false;

		result = m_System->setSpeakerMode(m_SpeakerMode);
		if(!FMODCheckError(result))
			return false;

		if(m_Caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = m_System->setDSPBufferSize(1024, 10);
			if(!FMODCheckError(result))
				return false;
		}

		// Get name of driver
		result = m_System->getDriverInfo(0, name, 256, 0);
		if(!FMODCheckError(result))
			return false;

		if(strstr(name, "SigmaTel"))
		{
			result = m_System->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			if(!FMODCheckError(result))
				return false;
		}
	}

	// Init FMOD
	result = m_System->init(100, FMOD_INIT_NORMAL, 0);

	if(result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = m_System->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if(!FMODCheckError(result))
			return false;

		result = m_System->init(100, FMOD_INIT_NORMAL, 0);
	}
	if(!FMODCheckError(result))
		return false;

	result = m_System->createChannelGroup(NULL, &m_ChannelMusic);
	if(!FMODCheckError(result))
		return false;

	result = m_System->createChannelGroup(NULL, &m_ChannelSFX);
	if(!FMODCheckError(result))
		return false;

	return true;
}

void SoundManager::Release( void )
{
	FMOD_RESULT result;

	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		m_Sounds[i]->sound->release();
		delete[] m_Sounds[i]->filename;
		delete m_Sounds[i];
	}
	m_Sounds.clear();

	result = m_System->release();
	// error check
}

void SoundManager::Update( void )
{
	FMOD_RESULT result;
	result = m_System->update();
}

int SoundManager::LoadMusic( const char* _fileName )
{
	FMOD_RESULT result;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		if(strcmp(m_Sounds[i]->filename, _fileName) == 0)
		{
			return i;
		}
	}
	Sounds* newSound = new Sounds();
	// open music as a stream
	result = m_System->createStream(_fileName, FMOD_DEFAULT, 0, &newSound->sound);
	//error check

	// Assign song to a channel, and start paused
	result = m_System->playSound(FMOD_CHANNEL_FREE, newSound->sound, true, &newSound->channel);
	// error check
	newSound->isSFX = false;

	if(newSound->filename == nullptr)
		newSound->filename = new char[strlen(_fileName) + 1];

	strcpy_s(newSound->filename, strlen(_fileName) + 1, _fileName);

	m_Sounds.push_back(newSound);

	newSound->channel->setChannelGroup(m_ChannelMusic);

	return m_CurrSounds++;
}

int SoundManager::LoadSFX( const char* _fileName )
{
	FMOD_RESULT result;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		if(strcmp(m_Sounds[i]->filename, _fileName) == 0)
		{
			return i;
		}
	}
	Sounds* newSound = new Sounds();
	// open music as a stream
	result = m_System->createSound(_fileName, FMOD_DEFAULT, 0, &newSound->sound);
	//error check

	// Assign song to a channel, and start paused
	result = m_System->playSound(FMOD_CHANNEL_FREE, newSound->sound, true, &newSound->channel);
	// error check
	newSound->isSFX = true;

	if(newSound->filename == nullptr)
		newSound->filename = new char[strlen(_fileName) + 1];

	strcpy_s(newSound->filename, strlen(_fileName) + 1, _fileName);

	m_Sounds.push_back(newSound);

	//newSound->channel->setChannelGroup(m_ChannelSFX);

	return m_CurrSounds++;
}

void SoundManager::Play( int _soundID, bool _isLooping, bool _startOver )
{
	Sounds* temp = m_Sounds[_soundID];

	if(temp->isSFX)
	{
		temp->channel->setChannelGroup(m_ChannelSFX);
		int index = 0;
		temp->channel->getIndex(&index);
		m_System->playSound((FMOD_CHANNELINDEX)index, temp->sound, false, &temp->channel);
	}
	else
		temp->channel->setPaused(false);

	bool paused, isplaying;
	temp->channel->getPaused(&paused);
	isplaying = IsPlaying(_soundID);

	if((paused == false && isplaying == false) || _startOver == true)
	{
		int index = 0;
		temp->channel->getIndex(&index);
		m_System->playSound((FMOD_CHANNELINDEX)index, temp->sound, _isLooping, &temp->channel);
	}

	if(_isLooping)
	{
		temp->channel->setLoopCount(-1);
	}
	else
	{
		temp->channel->setLoopCount(0);
	}
}

void SoundManager::PauseAllMusic()
{
	Sounds* temp;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		temp = m_Sounds[i];
		if(!temp->isSFX)
			temp->channel->setPaused(true);
	}
}

void SoundManager::UnpauseAllMusic()
{
	Sounds* temp;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		temp = m_Sounds[i];
		if(!temp->isSFX)
			temp->channel->setPaused(false);
	}
}

void SoundManager::PauseAllSFX()
{
	Sounds* temp;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		temp = m_Sounds[i];
		if(temp->isSFX)
			temp->channel->setPaused(true);
	}
}

void SoundManager::UnpauseAllSFX()
{
	Sounds* temp;
	for(unsigned int i = 0; i < m_Sounds.size(); ++i)
	{
		temp = m_Sounds[i];
		if(temp->isSFX)
			temp->channel->setPaused(false);
	}
}

void SoundManager::Pause( int _soundID )
{
	Sounds* temp;
	temp = m_Sounds[_soundID];
	temp->channel->setPaused(true);
}

void SoundManager::Unpause( int _soundID )
{
	Sounds* temp;
	temp = m_Sounds[_soundID];
	temp->channel->setPaused(false);
}

bool SoundManager::IsPlaying( int _soundID )
{
	Sounds* temp = m_Sounds[_soundID];
	bool isPlaying;
	temp->channel->isPlaying(&isPlaying);
	return isPlaying;
}