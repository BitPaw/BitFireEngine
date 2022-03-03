#pragma once

#include <Math/Geometry/Matrix4x4.hpp>
#include "../Shader/ShaderProgram.h"
#include "../System/RenderMode.h"

namespace BF
{
	struct Renderable : public Matrix4x4<float>
	{
		public:  
		unsigned int VAO;
		unsigned int VBO;
		unsigned int IBO;

		unsigned int ShaderID;
		unsigned int TextureID;

		RenderMode Mode;

		bool ShouldItBeRendered;

		Renderable();

		void MeshShare(const Renderable& rendable);
		void ShaderUse(const ShaderProgram& shaderProgram);
	};
}