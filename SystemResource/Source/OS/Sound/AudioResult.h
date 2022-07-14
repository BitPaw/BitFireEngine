#pragma once

namespace BF
{
	enum class AudioResult
	{
		Invalid,

		Sucessful,

		DeviceIDInvalid,
		DeviceHandleInvalid,
		DeviceNoDriver,

		DriverNotReachable, // Maybe diabled, or deactivated
		DriverNotEnabled, // No driver to use
		

		DeviceAlreadyAllocated,
		OutOfMemory,

		NotSupported,

		ErrorValueInvalid,

	
		FlagInvalid,
		ParameterInvalid,
	
		DeviceHandleBusy,

		AliasNotFound,



		RegistryValueNotFound,

		DriverNoCallback,

		MoreData,


		// Custom
		DeviceListNotBigEnough,


		// Windows spesific
		RegistryDatabaseInvalid,
		RegistryKeyNotFound,
		RegistryWriteError,
		RegistryReadError,
		RegistryDeleteError,

		ErrorUnspecified, 		// Bad, but windows, am i right?



		// only
		WaveFormatUnsupported,
		DeviceIsStillPlaying,
		ReaderIsNotPrepared,
		DeviceIsSynchronous
	};
}