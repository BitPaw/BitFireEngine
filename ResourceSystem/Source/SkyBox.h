#pragma once

#include "Resource.h"
#include "Image/Image.h"
#include "Shader/ShaderProgram.h"

namespace BF
{
	class SkyBox : public Resource
	{
		public:
		ShaderProgram Shader;
		
        unsigned int VAOID;
        unsigned int VBOID;
        unsigned int IndexID;

        unsigned int IndexData[24] =
        {
            1,3,5,7,
            2,4,6,8,
            3,4,7,8,
            5,6,7,8,
            1,2,3,4,
            1,2,5,6
        };

        float SkyboxVertices[24] =
        {
            1.0f, 1.0f, -1.0f,

            1.0f, -1.0f, -1.0f,

             1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,

            -1.0f, 1.0f, 1.0f,

            -1.0f, -1.0f, 1.0f
        };

		Image Faces[6];

        SkyBox();
	};
}