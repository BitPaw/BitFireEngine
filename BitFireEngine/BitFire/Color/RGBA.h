#pragma once

#include "RGB.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../Mathematic/Interpolate.h"

class RGBA : public RGB
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