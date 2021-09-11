#pragma once

#include "../Player/Player.h"

#include "../../../SystemRender/Source/Window/Window.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/Event/Event.hpp"
#include "../../../BitFireEngine/Source/Resource/ResouceManager.h"
#include "IBitFireEngineListener.hpp"
#include "../../../SystemSound/Source/SystemSound.h"

namespace BF
{
	class BitFireEngine
	{
		private:
		//---[Elements}---------------------------------
		StopWatch _stopWatch;
		Window _mainWindow;
		float _deltaTime;
		//----------------------------------------------

		void UpdateInput(InputContainer& input);

		public:
		//GameTickEvent OnGameTick;
		//LevelManager Level;
		ResourceManager Resource;
		bool IsRunning;
		IBitFireEngineListener* _callbackListener;
		SystemSound SoundPlayer;

		BitFireEngine();

		void SetCallBack(IBitFireEngineListener* callbackListener);

		void Start();
		void Update();
		void Stop();
	};
}