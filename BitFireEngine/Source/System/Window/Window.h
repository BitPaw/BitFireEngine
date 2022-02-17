#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Container/Dictionary.hpp>
#include <Container/AsciiString.h>
#include <Image/Image.h>

#include "../RefreshRateMode.h"
#include "../Device/Mouse/CursorMode.h"
#include "../Device/InputContainer.h"
#include "IWindowListener.h"

namespace BF
{
	class Window
	{
		private:
		GLFWwindow* _window;
		GLFWcursor* _cursor;
		GLFWmonitor* _montor;		

		public:
		static Dictionary<GLFWwindow*, Window*> WindowLookup;

		InputContainer Input;

		float ActiveTime;
		bool ShouldCloseWindow;

		unsigned int Width;
		unsigned int Height;	

		Window();
		~Window();		

		IWindowListener* Callback;		

		static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void OnMousePosition(GLFWwindow* window, double xpos, double ypos);
		static void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height);
		static void OnGLFWError(int errorCode, const char* description);

		static Window* GetWindow(GLFWwindow* window)
		{
			Window** result = WindowLookup.GetValue(window);

			if (result)
			{
				return *result;
			}

			return nullptr;
		}

		bool Create(int width, int height, const char* title);

		double GetTime();

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
		void SetTitle(AsciiString& title);

		/*
		Changed the icon that is shown in the taskbar.

		@param The image that will be used.
		*/
		void SetIcon(Image* image);

		/*
		Takes a picture of the curently rendered image.

		@return Image of the current scene.
		*/
		void TakeScreenShot(Image& image);

		//bool ShouldExit();

		void Update();
	};
}