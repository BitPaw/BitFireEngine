#pragma once

#include "AudioResult.h"
#include "AudioDeviceCapabilities.h"
#include "AudioDeviceInput.h"
#include "AudioDeviceOutput.h"

namespace BF
{
	class AudioSystem
	{
		public:

		AudioResult OutputOpen
		(
			AudioDeviceOutput& audioDeviceOutput,
			unsigned int deviceID,
			unsigned short formatTag,         /* format type */
			unsigned short channels,          /* number of channels (i.e. mono, stereo...) */
			unsigned int samplesPerSec,     /* sample rate */
			unsigned int avgBytesPerSec,    /* for buffer estimation */
			unsigned short blockAlign,        /* block size of data */
			unsigned short bitsPerSample,     /* number of bits per sample of mono data */
			unsigned short cbSize             /* the count in bytes of the size of */		
		);
		AudioResult OutputPrepare(AudioDeviceOutput& audioDeviceOutput);
		AudioResult OutputWrite
		(
			AudioDeviceOutput& audioDeviceOutput,
			void* dataBuffer,
			size_t bufferLength,
			unsigned int bytesRecorded,
			unsigned int user,
			unsigned int flags,
			unsigned int loopControlCounter
		);
		AudioResult OutputClose(AudioDeviceOutput& audioDeviceOutput);
		AudioResult OutputVolumeGet(AudioDeviceOutput& audioDeviceOutput, unsigned short& volume);

		AudioResult OutputVolumeSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int volume);
		AudioResult OutputVolumeSet(AudioDeviceOutput& audioDeviceOutput, const unsigned short volumeLeft, const unsigned short volumeRight);
		AudioResult OutputPause(AudioDeviceOutput& audioDeviceOutput);
		AudioResult OutputPitchSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int pitch);
		AudioResult OutputPlaybackRateSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int pitch);


		AudioResult DevicesFetchOutput(AudioDeviceCapabilities* audioDeviceCapabilitiesList, const size_t audioDeviceCapabilitiesListSizeMax, size_t& audioDeviceCapabilitiesListSize);
		AudioResult DevicesFetchInput(AudioDeviceCapabilities* audioDeviceCapabilitiesList, const size_t audioDeviceCapabilitiesListSizeMax, size_t& audioDeviceCapabilitiesListSize);
	};
}