#pragma once

#include "../../BitFireEngine/Source/System/BitFireEngine.h"

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
	};
}