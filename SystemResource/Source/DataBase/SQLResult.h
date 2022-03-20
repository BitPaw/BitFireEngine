#pragma once

namespace BF
{
	enum class SQLResult
	{
		Invalid,

		Successful,

		ConnectionFailed,

		DatabaseNotConnected, // Trying to use a command that requires an already established connection.

		MemoryAllocFailed,
		MemoryFreeFailed,

		SettingEnvironmentAttributeFailed,

		ExecuteFailed
	};
}