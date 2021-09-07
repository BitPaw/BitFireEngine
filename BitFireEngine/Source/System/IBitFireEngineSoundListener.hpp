#pragma once

#include "../../../SystemResource/Source/Sound/Sound.h"

namespace BF
{
	class IBitFireEngineRenderListener
	{
		public:
		virtual void Register(Sound& sound) = 0;

		virtual void Play(Sound& sound) = 0;

		virtual void UnRegister(Sound& sound) = 0;
	};
}