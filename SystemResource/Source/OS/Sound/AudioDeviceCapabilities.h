#pragma once

#define SoundDeviceProductName 32u

namespace BF
{
	enum class AudioDeviceType
	{
		Invalid,

		Input,
		Output
	};

	class AudioDeviceCapabilities
	{
		public:
		AudioDeviceType Type;
		unsigned int DeviceID;
		unsigned short ManufacturerID;
		unsigned short ProductID;       
		unsigned short DriverVersionMajor;
		unsigned short DriverVersionMinor;

		wchar_t ProductName[SoundDeviceProductName];

		unsigned int   dwFormats;             /* formats supported */
		unsigned short Channels;
		unsigned int  dwSupport;             /* functionality supported by driver */

		void Prinf();
	};
}