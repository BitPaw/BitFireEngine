#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

#include "InputContainer.h"

#include "../../Graphics/Camera/FirstPersonCamera.h"
#include "../../Time/TimeCollection.h"
#include "../../Configuration/VideoConfig.h"
#include "../../Player/Player.h"
#include "../../Mathematic/Interpolate.h"
#include "../../Resources/Image/Image.h"

namespace BF
{
	class Window
	{
	private:
		static Window* _instance;
		GLFWwindow* _window;
		GLFWcursor* _cursor;
		GLFWmonitor* _montor;
		bool _exitWindow;

		void UpdateInput();
		bool Create();

	public:
		static Window* GetInstance();

		Player* CurrentPlayer;

		Window(Player* player);
		~Window();

		/*
		Changed the size of this window.

		@param Width of this window.			
		@param Height of this window.
		*/
		void Resize(const unsigned int width, const unsigned int height);

		/*
		Changed the cursor mode in this window.	

		Default: The cursor is shown. 
		Hidden: Useful when you are in playmode.

		@param Mode of the cursor. Hide or show cursor.
		*/
		void SetCursorMode(CursorMode mode);

		/*
		Changed the cursor texture in this window.
		if the Cursor is not hidden.

		@param Texture of the cursor.
		*/
		void SetCursorTexture(Image* image);
		
		/*
		Changed the title for this window.
		The Text on top of this window.

		@param The title.
		*/
		void SetVideoRefreshRate(RefreshRateMode mode);
			
		/*
		Move this windows in the middle of the primary screen.
		*/
		void SetPositionToCenter();

		/*
		Move this window to a specific location.	

		@param X Position
		@param Y Position
		*/
		void SetPosition(unsigned int x, unsigned int y);

		/*
		Changed the title for this window.
		The Text on top of this window.

		@param The title.
		*/
		void SetTitle(std::string title);

		/*
		Changed the icon that is shown in the taskbar.

		@param The image that will be used.
		*/
		void SetIcon(Image* image);

		/*
		Takes a picture of the curently rendered image.

		@return Image of the current scene.
		*/
		Image* TakeScreenShot();

		bool ShouldExit();

		void Update();
	};
}