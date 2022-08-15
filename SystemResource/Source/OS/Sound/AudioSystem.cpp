#include "AudioSystem.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <windows.h>
#include <mmeapi.h>

#pragma comment( lib, "winmm.lib" )

BF::AudioResult ConvertMMResult(const unsigned int mmResultID)
{
	switch(mmResultID)
	{
		case MMSYSERR_NOERROR:  return BF::AudioResult::Sucessful;
		case MMSYSERR_ERROR:return BF::AudioResult::ErrorUnspecified;
		case MMSYSERR_BADDEVICEID:  return BF::AudioResult::DeviceIDInvalid;
		case MMSYSERR_NOTENABLED:   return BF::AudioResult::DriverNotEnabled;
		case MMSYSERR_ALLOCATED: return BF::AudioResult::DeviceAlreadyAllocated;
		case MMSYSERR_INVALHANDLE:  return BF::AudioResult::DeviceHandleInvalid;
		case MMSYSERR_NODRIVER:   return BF::AudioResult::DeviceNoDriver;
		case MMSYSERR_NOMEM:return BF::AudioResult::OutOfMemory;
		case MMSYSERR_NOTSUPPORTED: return BF::AudioResult::NotSupported;
		case MMSYSERR_BADERRNUM:  return BF::AudioResult::ErrorValueInvalid;
		case MMSYSERR_INVALFLAG: return BF::AudioResult::FlagInvalid;
		case MMSYSERR_INVALPARAM: return BF::AudioResult::ParameterInvalid;
		case MMSYSERR_HANDLEBUSY:return BF::AudioResult::DeviceHandleBusy;
		case MMSYSERR_INVALIDALIAS:return BF::AudioResult::AliasNotFound;
		case MMSYSERR_BADDB: return BF::AudioResult::RegistryDatabaseInvalid;
		case MMSYSERR_KEYNOTFOUND: return BF::AudioResult::RegistryKeyNotFound;
		case MMSYSERR_READERROR:  return BF::AudioResult::RegistryReadError;
		case MMSYSERR_WRITEERROR: return BF::AudioResult::RegistryWriteError;
		case MMSYSERR_DELETEERROR:   return BF::AudioResult::RegistryDeleteError;
		case MMSYSERR_VALNOTFOUND: return BF::AudioResult::RegistryValueNotFound;
		case MMSYSERR_NODRIVERCB:  return BF::AudioResult::DriverNoCallback;
		case MMSYSERR_MOREDATA:   return BF::AudioResult::MoreData;

		case WAVERR_BADFORMAT: return BF::AudioResult::WaveFormatUnsupported;
		case WAVERR_STILLPLAYING: return BF::AudioResult::DeviceIsStillPlaying;
		case WAVERR_UNPREPARED: return BF::AudioResult::ReaderIsNotPrepared;
		case WAVERR_SYNC: return BF::AudioResult::DeviceIsSynchronous;

		default:
			return BF::AudioResult::Invalid;
	}
}

#endif
#include <Text/Text.h>



BF::AudioResult BF::AudioSystem::OutputOpen
(
	AudioDeviceOutput& audioDeviceOutput,
	unsigned int deviceID,
	unsigned short formatTag,
	unsigned short channels,
	unsigned int samplesPerSec,
	unsigned int avgBytesPerSec,
	unsigned short blockAlign,
	unsigned short bitsPerSample,
	unsigned short cbSize
)
{
#if defined(OSUnix)
	return AudioResult::Invalid;

#elif defined(OSWindows)
	WAVEFORMATEX waveFormatEX{0};
	DWORD_PTR dwCallback = 0;
	DWORD_PTR dwInstance = 0;
	DWORD fdwOpen = CALLBACK_NULL;

	waveFormatEX.wFormatTag = formatTag;
	waveFormatEX.nChannels = channels;
	waveFormatEX.nSamplesPerSec = samplesPerSec;
	waveFormatEX.nAvgBytesPerSec = avgBytesPerSec;
	waveFormatEX.nBlockAlign = blockAlign;
	waveFormatEX.wBitsPerSample = bitsPerSample;
	waveFormatEX.cbSize = cbSize;

	const MMRESULT result = waveOutOpen
	(
		&audioDeviceOutput.Handle,
		deviceID,
		&waveFormatEX,
		dwCallback,
		dwInstance,
		fdwOpen
	);
	const AudioResult audioResult = ConvertMMResult(result);

	return audioResult;
#endif
}

BF::AudioResult BF::AudioSystem::OutputPrepare(AudioDeviceOutput& audioDeviceOutput)
{
#if defined(OSUnix)
#elif defined(OSWindows)
#endif

	return AudioResult::Invalid;
}

BF::AudioResult BF::AudioSystem::OutputWrite
(
	AudioDeviceOutput& audioDeviceOutput,
	void* dataBuffer,
	size_t bufferLength,
	unsigned int bytesRecorded,
	unsigned int user,
	unsigned int flags,
	unsigned int loopControlCounter
)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	WAVEHDR waveHeader{0};
	const UINT cbwh = sizeof(waveHeader);

	waveHeader.lpData = (LPSTR)dataBuffer;
	waveHeader.dwBufferLength = bufferLength;
	waveHeader.dwBytesRecorded = bytesRecorded;
	waveHeader.dwUser = user;
	waveHeader.dwFlags = flags;
	waveHeader.dwLoops = loopControlCounter;

	// Prepare
	{
		const MMRESULT prepareResultID = waveOutPrepareHeader(audioDeviceOutput.Handle, &waveHeader, cbwh);
		const AudioResult prepareResult = ConvertMMResult(prepareResultID);
		const bool wasSucessful = prepareResult == AudioResult::Sucessful;

		if(!wasSucessful)
		{
			return prepareResult;
		}
	}

	// Write Data
	{
		const MMRESULT writeResultID = waveOutWrite(audioDeviceOutput.Handle, &waveHeader, cbwh);
		const AudioResult writeResult = ConvertMMResult(writeResultID);
		const bool wasSucessful = writeResult == AudioResult::Sucessful;

		if(!wasSucessful)
		{
			return writeResult;
		}
	}
#endif

	return AudioResult::Sucessful;
}

BF::AudioResult BF::AudioSystem::OutputClose(AudioDeviceOutput& audioDeviceOutput)
{
#if defined(OSUnix)
	return AudioResult::Invalid;

#elif defined(OSWindows)

	const MMRESULT result = waveOutClose(audioDeviceOutput.Handle);
	const AudioResult audioResult = ConvertMMResult(result);

	audioDeviceOutput.Handle = 0;

	return audioResult;

#endif
}

BF::AudioResult BF::AudioSystem::OutputVolumeGet(AudioDeviceOutput& audioDeviceOutput, unsigned short& volume)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	DWORD volumeDW = 0;

	const MMRESULT volumeResultID = waveOutGetVolume(audioDeviceOutput.Handle, &volumeDW);
	const AudioResult audioResult = ConvertMMResult(volumeResultID);
	const bool sucessful = audioResult == AudioResult::Sucessful;

	if(!sucessful)
	{
		volume = 0;
		return audioResult;
	}

	volume = volumeDW;
#endif

	return AudioResult::Sucessful;
}

BF::AudioResult BF::AudioSystem::OutputVolumeSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int volume)
{
#if defined(OSUnix)
    return AudioResult::Sucessful;

#elif defined(OSWindows)
	const MMRESULT volumeResultID = waveOutSetVolume(audioDeviceOutput.Handle, volume);
	const AudioResult audioResult = ConvertMMResult(volumeResultID);

	return audioResult;
#endif
}

BF::AudioResult BF::AudioSystem::OutputVolumeSet(AudioDeviceOutput& audioDeviceOutput, const unsigned short volumeLeft, const unsigned short volumeRight)
{
	unsigned int volumeCombined = (volumeLeft << 16) | volumeRight;
	const AudioResult audioResult = OutputVolumeSet(audioDeviceOutput, volumeCombined);

	return audioResult;
}

BF::AudioResult BF::AudioSystem::OutputPause(AudioDeviceOutput& audioDeviceOutput)
{
	return AudioResult();
}

BF::AudioResult BF::AudioSystem::OutputPitchSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int pitch)
{
#if defined(OSUnix)
	return AudioResult::Sucessful;

#elif defined(OSWindows)
	const MMRESULT pitchResultID = waveOutSetPitch(audioDeviceOutput.Handle, pitch);
	const AudioResult pitchResult = ConvertMMResult(pitchResultID);

	return pitchResult;
	#endif
}

BF::AudioResult BF::AudioSystem::OutputPlaybackRateSet(AudioDeviceOutput& audioDeviceOutput, const unsigned int pitch)
{
#if defined(OSUnix)
	return AudioResult::Sucessful;

#elif defined(OSWindows)
	const MMRESULT playbackRateResultID = waveOutSetPlaybackRate(		audioDeviceOutput.Handle,		pitch	);
	const AudioResult playbackRateResult = ConvertMMResult(playbackRateResultID);

	return playbackRateResult;
	#endif
}

BF::AudioResult BF::AudioSystem::DevicesFetchOutput(AudioDeviceCapabilities* audioDeviceCapabilitiesList, const size_t audioDeviceCapabilitiesListSizeMax, size_t& audioDeviceCapabilitiesListSize)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	const UINT numberOfPutpudevices = waveOutGetNumDevs();
	const bool isListBigEngough = numberOfPutpudevices < audioDeviceCapabilitiesListSizeMax;

	if(!isListBigEngough)
	{
		audioDeviceCapabilitiesListSize = 0;

		return AudioResult::DeviceListNotBigEnough;
	}

	for(size_t i = 0; i < numberOfPutpudevices; i++)
	{
		const UINT size = sizeof(WAVEOUTCAPSW);
		WAVEOUTCAPSW wAVEOUTCAPSW{0};

		const MMRESULT result = waveOutGetDevCapsW(i, &wAVEOUTCAPSW, size);
		const AudioResult audioResult = ConvertMMResult(result);
		const bool sucessful = audioResult == AudioResult::Sucessful;

		if(!sucessful)
		{
			return audioResult;
		}

		AudioDeviceCapabilities& audioDeviceCapabilities = audioDeviceCapabilitiesList[i];

		audioDeviceCapabilities.DeviceID = i;
		audioDeviceCapabilities.Type = AudioDeviceType::Output;
		audioDeviceCapabilities.ManufacturerID = wAVEOUTCAPSW.wMid;
		audioDeviceCapabilities.ProductID = wAVEOUTCAPSW.wPid;
		audioDeviceCapabilities.DriverVersionMajor = HIBYTE(wAVEOUTCAPSW.vDriverVersion);
		audioDeviceCapabilities.DriverVersionMinor = LOBYTE(wAVEOUTCAPSW.vDriverVersion);

		TextCopyW(wAVEOUTCAPSW.szPname, MAXPNAMELEN, audioDeviceCapabilities.ProductName, SoundDeviceProductName);

		audioDeviceCapabilities.Channels = wAVEOUTCAPSW.wChannels;
	}


	audioDeviceCapabilitiesListSize = numberOfPutpudevices;

	return AudioResult::Sucessful;
#endif
}

BF::AudioResult BF::AudioSystem::DevicesFetchInput(AudioDeviceCapabilities* audioDeviceCapabilitiesList, const size_t audioDeviceCapabilitiesListSizeMax, size_t& audioDeviceCapabilitiesListSize)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	const UINT numberOfInputDevices = waveInGetNumDevs();
	const bool isListBigEngough = numberOfInputDevices < audioDeviceCapabilitiesListSizeMax;

	if(!isListBigEngough)
	{
		audioDeviceCapabilitiesListSize = 0;

		return AudioResult::DeviceListNotBigEnough;
	}

	for(size_t i = 0; i < numberOfInputDevices; ++i)
	{
		WAVEINCAPSW waveInputCapabilitiesW{ 0 };
		const UINT waveInputCapabilitiesWSize = sizeof(waveInputCapabilitiesW);
		const MMRESULT result = waveInGetDevCapsW(i, &waveInputCapabilitiesW, waveInputCapabilitiesWSize);
		const AudioResult audioResult = ConvertMMResult(result);
		const bool sucessful = audioResult == AudioResult::Sucessful;

		if(!sucessful)
		{
			return audioResult;
		}

		AudioDeviceCapabilities& audioDeviceCapabilities = audioDeviceCapabilitiesList[i];

		audioDeviceCapabilities.Type = AudioDeviceType::Input;
		audioDeviceCapabilities.ManufacturerID = waveInputCapabilitiesW.wMid;
		audioDeviceCapabilities.ProductID = waveInputCapabilitiesW.wPid;
		audioDeviceCapabilities.DriverVersionMajor = HIBYTE(waveInputCapabilitiesW.vDriverVersion);
		audioDeviceCapabilities.DriverVersionMinor = LOBYTE(waveInputCapabilitiesW.vDriverVersion);

		TextCopyW(waveInputCapabilitiesW.szPname, MAXPNAMELEN, audioDeviceCapabilities.ProductName, SoundDeviceProductName);

		audioDeviceCapabilities.Channels = waveInputCapabilitiesW.wChannels;
	}

	audioDeviceCapabilitiesListSize = numberOfInputDevices;

	return AudioResult::Sucessful;
#endif
}
