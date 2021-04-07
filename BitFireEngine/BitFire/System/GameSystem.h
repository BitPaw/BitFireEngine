#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include "SystemState.h"
#include "GameTickEvent.h"
#include "GameTickData.h"

#include "../Utility/LinkedList.hpp"
#include "../Utility/Dictionary.hpp"

#include "../Resources/Image/Image.h"
#include "../Resources/Model/Model.h"
#include "../Resources/Sound/Sound.h"
#include "../Resources/Shader/Shader.h"
#include "../Resources/Shader/ShaderLoader.h"
#include "../Resources/Shader/ShaderProgram.h"

#include "../OpenGL/Window/Window.h"
#include "../Player/Player.h"
#include "../Configuration/ConfigContainer.h"

#include "../Graphics/Camera/FirstPersonCamera.h"

#include "../Resources/ResouceManager.h"
#include "../Time/StopWatch.h"

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

		void RenderScene();

	public:
		ConfigContainer Config;
		GameTickEvent OnGameTick;
		//LevelManager Level;
		ResourceManager Resource;

		bool IsRunning() { return _state == SystemState::Running; }

		void Start();
		void Update(); // private ??
		void UpdateInput(InputContainer* input);
		void Stop();

		static GameSystem& Instance() { return *(_instance == nullptr ? new GameSystem() : _instance); }

	
		GameSystem();

	};
}

#endif // !GAMESYSTEM_H