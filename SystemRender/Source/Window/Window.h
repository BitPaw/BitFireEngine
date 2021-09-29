#pragma once

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include "../../../Dependencies/include/GL/glew.h"
#include "../../../Dependencies/include/GLFW/glfw3.h"

#include "../../../SystemResource/Source/Container/Dictionary.hpp"
#include "../../../SystemResource/Source/Container/AsciiString.h"
#include "../../../SystemResource/Source/Image/Image.h"
#include "../RefreshRateMode.h"
#include "../Device/Mouse/CursorMode.h"
#include "../Device/InputContainer.h"

namespace BF
{
	class Window
	{
		private:
		GLFWwindow* _window;
		GLFWcursor* _cursor;
		GLFWmonitor* _montor;	

		public:
		float ActiveTime;
		bool ShouldCloseWindow;

		static int Width;
		static int Height;

		// Events
		//OnWindowCloseEvent OnWindowClose;

		Window();
		~Window();		

		static Dictionary<GLFWwindow*, InputContainer> WindowsInput;

		static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void OnMousePosition(GLFWwindow* window, double xpos, double ypos);
		static void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height);
		static void OnGLFWError(int errorCode, const char* description);

		InputContainer* GetInput()
		{
			return WindowsInput.GetValue(_window);
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