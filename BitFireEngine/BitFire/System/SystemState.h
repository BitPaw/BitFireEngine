#pragma once

namespace BF
{
	enum class SystemState
	{
		UnInitialized,

		Ready,

		Starting,
		Running,

		Stopping,
		Stopped
	};
}