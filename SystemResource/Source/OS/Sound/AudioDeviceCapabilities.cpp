#include "AudioDeviceCapabilities.h"

#include <stdio.h>

void BF::AudioDeviceCapabilities::Prinf()
{

	printf
	(
		"+----------------+--------+\n"
		"| Type           : %5i\n"
		"| DeviceID       : %5i\n"
		"| ManufacturerID : %5i\n"
		"| ProductID      : %5i\n"
		"| DriverVersion  : Major:%i, Minor:%i\n"
		"| ProductName    : %ls\n"
		"| Formats        : %i\n"
		"| Channels       : %i\n"
		"| Support        : %i\n"
		"+----------------+--------+\n",
		Type,
		DeviceID,
		ManufacturerID,
		ProductID,
		DriverVersionMajor,
		DriverVersionMinor,
		ProductName,
		dwFormats,
		Channels,
		dwSupport
	);
}