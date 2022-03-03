#pragma once

#include <System/BitFireEngine.h>
#include <System/Device/InputContainer.h>
#include <Camera/Camera.h>

namespace Cleaved
{
	class CleavedGameSystem : public BF::IBitFireEngineListener
	{
		public:
		BF::BitFireEngine GameSystem;

		CleavedGameSystem();

		virtual void OnUpdateUI() override;
		virtual void OnStartUp() override;
		virtual void OnShutDown() override;
		virtual void OnUpdateGameLogic(float deltaTime) override;
		virtual void OnUpdateInput(BF::InputContainer& input) override;
	};
}