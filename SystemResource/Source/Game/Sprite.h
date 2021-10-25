#pragma once

#include "../Model/Model.h"
#include "../Image/Image.h"

namespace BF
{
	class Sprite : public Model
	{
		public:
		Sprite();

		Image Texture;
		float TextureScale[2];

		void TextureScaleSet(float x, float y);
		void Set(float x, float y, float z, const char* name, const char* textureFilePath, Model* model = nullptr);
	};
}