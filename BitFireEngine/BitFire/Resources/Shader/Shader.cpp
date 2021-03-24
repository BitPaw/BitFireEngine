#include "Shader.h"

BF::Shader::Shader()
{
	ID = -1;
	Type = ShaderType::Unkown;
}

BF::Shader::Shader(ShaderType type, AsciiString& content) : Shader()
{
	Type = type;
	Content.Copy(content);
}