#include "SystemSound.h"

#include <cstdio>
#include <string>
#include <cassert>

BF::SystemSound::SystemSound()
{
	//---<Select Device>
	_audioDevice = alcOpenDevice(nullptr);

	if (!_audioDevice)
	{
		// Failed to get Sound device
		ALCenum error;

		error = alGetError();

		if (error != AL_NO_ERROR)
		{
			// something wrong happened
		}		
	}
	//----------------------------------------------


	// Create context
	_audioContext = alcCreateContext(_audioDevice, nullptr);
	bool contextCreationSuccessful = alcMakeContextCurrent(_audioContext);

	if (!contextCreationSuccessful)
	{
		// failed to make context current	
	}

	/*
	// test for errors here using alGetError();

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0, 0, 1.0f);
	// check for errors
	alListener3f(AL_VELOCITY, 0, 0, 0);
	// check for errors
	alListenerfv(AL_ORIENTATION, listenerOri);
	// check for errors

	*/
}

BF::SystemSound::~SystemSound()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(_audioContext);
	alcCloseDevice(_audioDevice);
}

void BF::SystemSound::Register(AudioSource& audioSource)
{
	const unsigned int numberOfBuffers = 1u;
	unsigned int& sourceID = audioSource.ID;

	alGenSources(numberOfBuffers, &audioSource.ID);
	// check for errors

	Update(audioSource);
}

void BF::SystemSound::Register(Sound& sound)
{
	const ALuint numberOfBuffers = 1;
	unsigned int id = 0;

	alGenBuffers(numberOfBuffers, &id);

	sound.ID = id;
}

void BF::SystemSound::UnRegister(AudioSource& audioSource)
{
	alDeleteSources(1, &audioSource.ID);
}

void BF::SystemSound::UnRegister(Sound& sound)
{
	unsigned int id = 0;

	alDeleteBuffers(1, &id);

	sound.ID = id;
}

void BF::SystemSound::Update(AudioSource& audioSource)
{
	alSourcef(audioSource.ID, AL_PITCH, audioSource.Pitch);
	// check for errors
	alSourcef(audioSource.ID, AL_GAIN, audioSource.Volume);
	// check for errors
	alSource3f(audioSource.ID, AL_POSITION, audioSource.Position[0], audioSource.Position[1], audioSource.Position[2]);
	// check for errors
	alSource3f(audioSource.ID, AL_VELOCITY, audioSource.Velocity[0], audioSource.Velocity[1], audioSource.Velocity[2]);
	// check for errors
	alSourcei(audioSource.ID, AL_LOOPING, audioSource.Looping);
}

void BF::SystemSound::Play(AudioSource& audioSource, Sound& sound)
{
	ALenum format = SystemSound::ToChannalFormat(sound.NumerOfChannels, sound.BitsPerSample);

	alBufferData(sound.ID, format, sound.Data, sound.DataSize, sound.SampleRate);
	// check for errors

	// Bind
	alSourcei(audioSource.ID, AL_BUFFER, sound.ID);
	// check for errors


	alSourcePlay(audioSource.ID);
	// check for errors

	//----<Check State>---------------
	//int sourceState;

	//alGetSourcei(audioSource.ID, AL_SOURCE_STATE, &sourceState);
	// check for errors
	//while (sourceState == AL_PLAYING)
	//{
		//alGetSourcei(audioSource.ID, AL_SOURCE_STATE, &sourceState);
		// check for errors
	//}
	//---------------------------------

}

void BF::SystemSound::LoopPart(AudioSource& audioSource, unsigned int startIndex, unsigned int endIndex)
{
	alSourcei(audioSource.ID, AL_BYTE_OFFSET, (ALint)startIndex);
	alSourcei(audioSource.ID, AL_SEC_OFFSET, (ALint)endIndex);
}

ALenum BF::SystemSound::ToChannalFormat(unsigned short numerOfChannels, unsigned short bitsPerSample)
{
	bool stereo = (numerOfChannels > 1);

	switch (bitsPerSample)
	{
		case 16u:
			return stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

		case 8u:
			return stereo ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;

		default:
			return -1;
	}
}
