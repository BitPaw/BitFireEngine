#pragma once

class Texture
{
public:
	unsigned int ColorValues;
	unsigned int Width;
	unsigned int Height;
	unsigned char* Data;

	Texture();
};