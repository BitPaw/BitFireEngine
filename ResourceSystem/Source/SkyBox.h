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

        unsigned int IndexData[36] =
        {
            5,3,1,
            5,7,3,

            2,8,6,
            2,4,8,

            3,8,4,
            3,7,8,

            7,6,8,
            7,5,6,

            1,4,2,
            1,3,4,

            5,1,2,
            5,2,6
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