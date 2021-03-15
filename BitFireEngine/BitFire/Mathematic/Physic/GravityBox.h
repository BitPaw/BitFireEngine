#pragma once

#include "GravityField.h"

namespace BF
{
	class GravityBox : public GravityField
	{
		public:
		virtual bool IsColliding(Point<float> position) override;
		virtual bool IsColliding(Position<float> position) override;
	};
}