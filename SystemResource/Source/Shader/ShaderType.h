#pragma once

namespace BF
{
	enum class ShaderType
	{
        Unkown,

        // .vert - a vertex shader
        Vertex,

        // .tesc - a tessellation control shader
        TessellationControl,

        // .tese - a tessellation evaluation shader
        TessellationEvaluation,

        // .geom - a geometry shader
        Geometry,
        
        // .frag - a fragment shader
        Fragment,

        // .comp - a compute shader
        Compute,
	};

    const char* ShaderTypeToString(ShaderType shaderType);
}