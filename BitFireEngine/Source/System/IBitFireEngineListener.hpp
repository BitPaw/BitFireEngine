#pragma once

namespace BF
{
	class IBitFireEngineListener
	{
		public:
		virtual void OnStartUp() = 0;
		virtual void OnShutDown() = 0;

		virtual void OnUpdateGameLogic(float deltaTime) = 0;
		virtual void OnUpdateUI() = 0;
		virtual void OnUpdateInput(InputContainer& input) = 0;
	};
}