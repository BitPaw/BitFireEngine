#pragma once

#include "IBitFireEngineListener.hpp"
#include "../Player/Player.h"
#include "../../../SystemRender/Source/Window/Window.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/Event/Event.hpp"
#include "../../../BitFireEngine/Source/Resource/ResouceManager.h"
#include "../../../SystemSound/Source/SystemSound.h"

namespace BF
{
	class BitFireEngine : protected IWindowListener
	{
		private:
		//---[Elements}---------------------------------
		StopWatch _stopWatch;
		Window _mainWindow;
		float _deltaTime;
		//----------------------------------------------


		// Geerbt über IWindowListener
		virtual void OnKeyPressed(int key, int scancode, int action, int mods) override;
		virtual void OnMouseButtonClick(int button, int action, int mods) override;
		virtual void OnMousePositionChanged(double positionX, double positionY) override;
		virtual void OnWindowSizeChanged(int width, int height) override;

		void UpdateInput(InputContainer& input);

		public:
		bool IsRunning;
		ResourceManager Resource;	
		SystemSound SoundPlayer;

		IBitFireEngineListener* _callbackListener;

		BitFireEngine();

		void SetCallBack(IBitFireEngineListener* callbackListener);

		void Start();
		void Update();
		void Stop();
	};
}