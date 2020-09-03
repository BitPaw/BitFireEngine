#pragma once


class RGBA
{
public:
	float Red;
	float Green;
	float Blue;
	float Alpha;

	RGBA();
	RGBA(float red, float green, float blue);
	RGBA(float red, float green, float blue, float alpha);

	//unsigned char GetRedAsByte();
	//unsigned char GetGreenAsByte();
	//unsigned char GetBlueAsByte();
	//unsigned char GetAlphaAsByte();
};