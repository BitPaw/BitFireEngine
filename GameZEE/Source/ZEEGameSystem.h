#pragma once

#include "../../BitFireEngine/Source/System/BitFireEngine.h"
#include "../../SystemRender/Source/Device/InputContainer.h"

namespace ZEE
{
	class ZEEGameSystem : public BF::IBitFireEngineListener
	{
		public:
		BF::BitFireEngine GameSystem;

		ZEEGameSystem();

		virtual void OnUpdateUI() override;
		virtual void OnStartUp() override;
		virtual void OnShutDown() override;
		virtual void OnUpdateGameLogic(float deltaTime) override;
		virtual void OnUpdateInput(BF::InputContainer& input) override;
	};
}