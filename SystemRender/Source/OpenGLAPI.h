#pragma once

#include "RenderMode.h"

#include "../../SystemResource/Source/Image/Image.h"
#include "../../SystemResource/Source/Shader/ShaderProgram.h"
#include "../../SystemResource/Source/Game/SkyBox.h"

namespace BF
{
	class OpenGLAPI
	{
		public:
		static void RegisterImage(Image& image);
		static void RegisterModel(Model& model);

		static void SkyBoxUse(SkyBox& skybox);
		static void SkyBoxSet(SkyBox& skybox);

		static void DepthMaskEnable(bool enable);
		static void DrawOrder(bool clockwise);
		static void RenderBothSides(bool renderBothSides);

		static void TextureUse(ImageType imageType, int textureID);

	
		// Render
		static void Render(RenderMode renderMode, int startIndex, int amount);
		static void RenderClear();

		// Data
		static void VertexAttributeArrayDefine(unsigned int sizeOfElement, unsigned int listSize, unsigned int* list);

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
		static bool ShaderCompile(ShaderProgram& shaderProgram);
		static unsigned int ShaderCompile(unsigned int type, char* shaderString);

		static int ShaderGetUniformLocationID(int shaderID, const char* UniformName);
		static void ShaderSetUniformMatrix4x4(int matrixUniformID, float* matrix);
		static void ShaderSetUniformVector3(int vector3UniformID, float x, float y, float z);
		static void ShaderSetUniformVector4(int vector3UniformID, float x, float y, float z, float w);

		static char UseShaderProgram(int shaderProgramID);
		static void VertexArrayBind(int vertexArrayID);
		static void VertexBufferBind(int vertexBufferID, int indexBuffer);

		// Converter
		private:
		static ShaderType ToShaderType(unsigned int token);
		static unsigned int ToShaderType(ShaderType shaderType);

		static ImageDataFormat ToImageFormat(unsigned int token);
		static unsigned int ToImageFormat(ImageDataFormat imageFormat);

		static ImageType ToImageType(unsigned int token);
		static unsigned int ToImageType(ImageType imageType);

		static int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
		static int ImageLayoutToOpenGLFormat(ImageLayout layout);

		static const char* ShaderTypeToString(int type);
	};
}