#include "ShaderType.h"

const char* BF::ShaderTypeToString(ShaderType shaderType)
{
	switch (shaderType)
	{
		default:
		case BF::ShaderType::Unkown:
			return "Unkown";

		case BF::ShaderType::Vertex:
			return "Vertex";

		case BF::ShaderType::TessellationControl:
			return "TessellationControl";

		case BF::ShaderType::TessellationEvaluation:
			return "TessellationEvaluation";

		case BF::ShaderType::Geometry:
			return "Geometry";

		case BF::ShaderType::Fragment:
			return "Fragment";

		case BF::ShaderType::Compute:
			return "Compute";
	}
}