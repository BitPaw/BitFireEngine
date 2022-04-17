#pragma once

#include <Media/Image/Image.h>

#include "TextureCube.h"
#include "Renderable.h"

#include <Shader/ShaderProgram.h>

namespace BF
{
	class SkyBox
	{
		public:		
		ShaderProgram Shader;
		Renderable RenderInfo;
		TextureCube Texture;

        SkyBox();
	};
}