#pragma once

#include "Window/Window.h"
#include "Shader/System/ShaderFile.h"
#include "Shader/System/ShaderLoader.h"

#include "../IO/Message/MessageSystem.h"
#include "../Player/Player.h"
#include "Render/RenderSystem.h"

namespace BF
{
	class OpenGLAPI
	{
	private:
		static OpenGLAPI* _instance;

		Player* _currentPlayer;

		OpenGLAPI();

	public:
		static OpenGLAPI* Instance();

		Window* MainWindow;
		RenderSystem* Render;

		void Initialize(Player* player);
		void Update();
		bool ShouldExit();


	};
}