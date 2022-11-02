#pragma once

#include "GravityField.h"

#include <Math/PXVector.h>

namespace BF
{
	class GravityCube : public GravityField
	{
		public:
		virtual bool IsColliding(PXVector2F* const position) override;
		virtual bool IsColliding(PXVector3F* const position) override;
	};
}