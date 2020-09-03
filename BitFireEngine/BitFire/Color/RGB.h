#pragma once

class RGB
{
public:
	float Red;
	float Green;
	float Blue;

	RGB();
	RGB(const float red, const float green, const float blue);

	virtual void SetColor(const float red, const float green, const float blue);
};