#pragma once

#define OpenGLUse

#include "RenderMode.h"

#include <Media/Image/Image.h>
#include <Model/Model.h>

#include "Texture.h"
#include "TextureCube.h"


#ifdef OpenGLUse
#define OpenGLInUse 1


#define OpenGLID unsigned int

namespace BF
{

	class OpenGL
	{
		public:
		static void Initialize();


		static OpenGLID ShaderProgramCreate();





		static void DepthMaskEnable(bool enable);
		static void DrawOrder(bool clockwise);
		static void RenderBothSides(bool renderBothSides);

		// Data
		static void VertexAttributeArrayDefine(const unsigned int sizeOfElement, const  unsigned int listSize, const unsigned int* list);

		static void VertexArrayDefine(unsigned int* vertexArrayID);
		static void VertexDataDefine(unsigned int* vertexID, int size, void* data);
		static void IndexDataDefine(unsigned int* indexID, int size, void* data);

		static void VertexArrayUpdate(int vertexArrayID, int size, void* data);

		// Getter
		static int TextureMaxSlots();
		static int TextureMaxLoaded();
		static const char* GLSLVersionPrimary();
		static void GLSLVersionsSupported(const char*** shaderList, int shaderListSize);
		static const char* GPUVendorName();
		static const char* GPUModel();

		// Shader
		static unsigned int ShaderCompile(unsigned int type, char* shaderString);

		static int ShaderGetUniformLocationID(int shaderID, const char* UniformName);
		static void ShaderSetUniformMatrix4x4(const int matrixUniformID, const float* matrix);
		static void ShaderSetUniformVector3(int vector3UniformID, float x, float y, float z);
		static void ShaderSetUniformVector4(int vector3UniformID, float x, float y, float z, float w);

		static char UseShaderProgram(int shaderProgramID);
		static void VertexArrayBind(int vertexArrayID);
		static void VertexBufferBind(int vertexBufferID, int indexBuffer);
	};
}
#endif