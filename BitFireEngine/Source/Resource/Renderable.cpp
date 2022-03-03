#include "Renderable.h"

BF::Renderable::Renderable()
{
	VAO = -1;
	VBO = -1;
	IBO = -1;

	ShaderID = -1;
	TextureID = -1;
	ShouldItBeRendered = true;

	Mode = RenderMode::Triangle;
}

void BF::Renderable::MeshShare(const Renderable& rendable)
{
	VAO = rendable.VAO;
	VBO = rendable.VBO;
	IBO = rendable.IBO;
}

void BF::Renderable::ShaderUse(const ShaderProgram& shaderProgram)
{
	ShaderID = shaderProgram.ID;
}