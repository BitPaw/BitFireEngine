#pragma once

namespace BF
{
	class IWindowListener
	{
		public:
		virtual void OnKeyPressed(int key, int scancode, int action, int mods) = 0;
		virtual void OnMouseButtonClick(int button, int action, int mods) = 0;
		virtual void OnMousePositionChanged(double positionX, double positionY) = 0;
		virtual void OnWindowSizeChanged(int width, int height) = 0;
	};
}