#ifndef ShaderInclude
#define ShaderInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
#pragma once

    typedef enum ShaderType_
    {
        ShaderTypeUnkown,
        ShaderTypeVertex,     // .vert - a vertex shader
        ShaderTypeTessellationControl,    // .tesc - a tessellation control shader
        ShaderTypeTessellationEvaluation,     // .tese - a tessellation evaluation shader
        ShaderTypeGeometry,      // .geom - a geometry shader
        ShaderTypeFragment,   // .frag - a fragment shader
        ShaderTypeCompute,   // .comp - a compute shader
    }
    ShaderType;

	typedef struct Shader_
	{
		ShaderType Type;
		size_t ContentSize;
		char* Content;
	}
	Shader;

	typedef struct ShaderProgram_
	{
		unsigned int ID;
	}
	ShaderProgram;

#ifdef __cplusplus
}
#endif

#endif