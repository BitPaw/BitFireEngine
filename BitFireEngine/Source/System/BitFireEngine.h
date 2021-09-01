#pragma once

#include "SystemState.h"
#include "GameTickData.h"

#include "../Player/Player.h"
#include "../Configuration/ConfigContainer.h"

#include "../../../RenderSystem/Source/Window/Window.h"
#include "../../../ResourceSystem/Source/Time/StopWatch.h"
#include "../../../ResourceSystem/Source/Event/Event.hpp"
#include "../../../BitFireEngine/Source/Resource/ResouceManager.h"
#include "IBitFireEngineListener.hpp"

namespace BF
{
	class BitFireEngine
	{
		private:
		//---[Elements}---------------------------------
		StopWatch _stopWatch;
		GameTickData _gameTickData;
		Window _mainWindow;
		//----------------------------------------------

		void UpdateInput(InputContainer* input);

		public:
		ConfigContainer Config;
		//GameTickEvent OnGameTick;
		//LevelManager Level;
		ResourceManager Resource;
		bool IsRunning;
		IBitFireEngineListener* _callbackListener;

		BitFireEngine();

		void SetCallBack(IBitFireEngineListener* callbackListener);

		void Start();
		void Update();
		void Stop();
	};
}