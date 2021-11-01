#pragma once

#include "../../../SystemResource/Source/Resource.h"
#include "../../../SystemResource/Source/Image/Image.h"
#include "../../../SystemResource/Source/Model/Model.h"
#include "../../../SystemResource/Source/Shader/ShaderProgram.h"

namespace BF
{
	class SkyBox : public Model
	{
		public:
		ShaderProgram Shader;
        Image Faces[6];

        SkyBox();
	};
}