#pragma once

#include "RGB.h"

class RGBA : public RGB
{
public:
	float Alpha;

	RGBA();
	RGBA(const float red, const float green, const float blue);
	RGBA(const float red, const float green, const float blue, const float alpha);

	void SetColor(const float red, const float green, const float blue) override;
	void SetColor(const float red, const float green, const float blue, const float alpha);
};