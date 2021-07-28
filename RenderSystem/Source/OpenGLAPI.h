#pragma once
#include "../../ResourceSystem/Source/Image/Image.h"
#include "RenderMode.h"
#include "../../ResourceSystem/Source/Shader/ShaderProgram.h"
#include "../../ResourceSystem/Source/SkyBox.h"

namespace BF
{
	class OpenGLAPI
	{
		public:
		static void RegisterImage(Image& image);
		static int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
        static int ImageLayoutToOpenGLFormat(ImageLayout layout);

		static void SkyBoxUse(SkyBox& skybox);
		static void SkyBoxSet(SkyBox& skybox);

		static void DepthMaskEnable(bool enable);

		static void TextureUse(ImageType imageType, int textureID);

		static char UseShaderProgram(int shaderProgramID);
		static void VertexArrayBind(int vertexArrayID);

		static void Render(RenderMode renderMode, int startIndex, int amount);
		static void RenderClear();

		static int TextureMaxSlots();
		static int TextureMaxLoaded();
		static const char* VersionName();

		static void VertexArrayUpdate(int vertexArrayID, int size, void* data);

		static bool ShaderCompile(ShaderProgram& shaderProgram);
		static unsigned int ShaderCompile(unsigned int type, char* shaderString);

		static void VertexAttributeArrayDefine(int sizeOfElement, int listSize, int* list);

		static void VertexArrayDefine(unsigned int* vertexArrayID);
		static void VertexDataDefine(unsigned int* vertexID, int size, void* data);
		static void IndexDataDefine(unsigned int* indexID, int size, void* data);

		static int ShaderGetUniformLocationID(int shaderID, const char* UniformName);
		static void ShaderSetUniformMatrix4x4(int matrixUniformID, float* matrix);

		static const char* ShaderTypeToString(int type);


		static ImageType ToImageType(unsigned int token);
		static unsigned int  FromImageType(ImageType imageType);
	};
}

/*

	glLineWidth(10);
	glPointSize(5);
*/