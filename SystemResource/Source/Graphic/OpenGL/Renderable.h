#pragma once

#include <Math/Geometry/Matrix4x4.hpp>
#include <Shader/ShaderProgram.h>
#include "RenderMode.h"
#include "RenderableChunk.h"

#include <Container/List.hpp>
#include <Shader/ShaderProgram.h>

namespace BF
{
	struct Renderable : public Matrix4x4<float>
	{
		public:  

		bool DoRendering;

		unsigned int ID; // VAO
		unsigned int ChunkListSize;
		RenderableChunk* ChunkList;

		Renderable* Parent;
		List<Renderable*> Children;

		RenderMode Mode;

		Renderable();

		void MeshShare(const Renderable& rendable);
		void ShaderUse(const ShaderProgram& shaderProgram);
		void ShaderUse(const unsigned int shaderProgramID);


		void TextureUse(const unsigned int texturteID);
		//void TextureUse(const Textrue& texturteID);

		constexpr bool IsRegistered() const { return ID != -1; } ;
	};
}