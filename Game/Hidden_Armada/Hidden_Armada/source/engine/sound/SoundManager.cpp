#include "SoundManager.h"

#include <string.h>

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

	result = FMOD::System_Create(&m_System);
	if(!FMODErrorCheck(result))
		return false;

	result = m_System->getVersion(&version);
	if(!FMODErrorCheck(result))
		return false;

	if(version < FMOD_VERSION)
		return false;

	result = m_System->getNumDrivers(&numDrivers);
	if(!FMODErrorCheck(result))
		return false;

	// No sound cards (disable sound)
	if(numDrivers == 0)
	{
		result = m_System->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if(!FMODErrorCheck(result))
			return false;
	}
	// At least one sound card
	else
	{
		result = m_System->getDriverCaps(0, &m_Caps, 0, &m_SpeakerMode);
		if(!FMODErrorCheck(result))
			return false;

		result = m_System->setSpeakerMode(m_SpeakerMode);
		if(!FMODErrorCheck(result))
			return false;

		if(m_Caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = m_System->setDSPBufferSize(1024, 10);
			if(!FMODErrorCheck(result))
				return false;
		}

		// Get name of driver
		result = m_System->getDriverInfo(0, name, 256, 0);
		if(!FMODErrorCheck(result))
			return false;

		if(strstr(name, "SigmaTel"))
		{
			result = m_System->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			if(!FMODErrorCheck(result))
				return false;
		}
	}

	// Init FMOD
	result = m_System->init(100, FMOD_INIT_NORMAL, 0);

	if(result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = m_System->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if(!FMODErrorCheck(result))
			return false;

		result = m_System->init(100, FMOD_INIT_NORMAL, 0);
	}
	if(!FMODErrorCheck(result))
		return false;

	return true;
}

void SoundManager::Release( void )
{

}
