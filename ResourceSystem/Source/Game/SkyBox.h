#pragma once

#include "../../../ResourceSystem/Source/Resource.h"
#include "../../../ResourceSystem/Source/Image/Image.h"
#include "../../../ResourceSystem/Source/Shader/ShaderProgram.h"

namespace BF
{
	class SkyBox : public Resource
	{
		public:
		ShaderProgram Shader;
        		
        unsigned int VAOID;
        unsigned int VBOID;
        unsigned int IndexID;

#if 0
        unsigned int IndexData[24] =
        {
            1,3,5,7,
            2,4,6,8,
            3,4,7,8,
            5,6,7,8,
            1,2,3,4,
            1,2,5,6
        };
#else
        unsigned int IndexList[36] =
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
#endif

        float SkyboxVertices[108] =
        {
	  -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,

	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,

	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,

	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,

	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,

	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,

	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,

	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,

	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
        };

		Image Faces[6];

        SkyBox();
	};
}