#pragma once

#include "AudioSource.h"
#include "../../Dependencies/include/AL/al.h"
#include "../../Dependencies/include/AL/alc.h"
#include "../../SystemResource/Source/Sound/Sound.h"

namespace BF
{
	class SystemSound 
	{
		private:
		ALCdevice* _audioDevice;
		ALCcontext* _audioContext;

		public:
		SystemSound();
		~SystemSound();	

		void Register(AudioSource& audioSource);
		void Register(Sound& sound);
		void UnRegister(AudioSource& audioSource);
		void UnRegister(Sound& sound);

		void Update(AudioSource& audioSource);

		void Play(AudioSource& audioSource, Sound& sound);
		void LoopPart(AudioSource& audioSource, unsigned int startIndex, unsigned int endIndex);

		

		static ALenum ToChannalFormat(unsigned short numerOfChannels, unsigned short bitsPerSample);
	};
}