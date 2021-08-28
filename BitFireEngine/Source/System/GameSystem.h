#pragma once

#include "SystemState.h"
#include "GameTickData.h"

#include "../Player/Player.h"
#include "../Configuration/ConfigContainer.h"

#include "../../../RenderSystem/Source/Window/Window.h"
#include "../../../ResourceSystem/Source/Time/StopWatch.h"
#include "../../../BitFireEngine/Source/Resource/ResouceManager.h"

namespace BF
{
	class GameSystem
	{
		private:
		static GameSystem* _instance;

		SystemState _state;

		//---[Elements}---------------------------------
		StopWatch _stopWatch;
		GameTickData _gameTickData;
		Window _mainWindow;
		//----------------------------------------------

		public:
		ConfigContainer Config;
		//GameTickEvent OnGameTick;
		//LevelManager Level;
		ResourceManager Resource;

		bool IsRunning() { return _state == SystemState::Running; }

		void Start();
		void Update(); // private ??
		void UpdateInput(InputContainer* input);
		void UpdateUI();
		void Stop();

		static GameSystem& Instance() { return *(_instance == nullptr ? new GameSystem() : _instance); }


		GameSystem();

	};
}