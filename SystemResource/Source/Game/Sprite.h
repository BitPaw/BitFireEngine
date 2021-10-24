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

		void Set(float x, float y, float z, const char* name, const char* textureFilePath, Model* model = nullptr);
	};
}