#pragma once

#include "RGB.h"

#include "../Mathematic/Math.h"

namespace BF
{
	struct RGBA : public RGB
	{
	public:
		float Alpha;

		RGBA();
		RGBA(const float red, const float green, const float blue);
		RGBA(const float red, const float green, const float blue, const float alpha);

		void SetColor(const float red, const float green, const float blue) override;
		void SetColor(const float red, const float green, const float blue, const float alpha);

		static RGBA GetRandomeColor();
	};
}