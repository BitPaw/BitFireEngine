#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "RenderDataCache.h"

#include "../Window/Window.h"
#include "../Shader/System/ShaderFile.h"
#include "../Shader/System/ShaderLoader.h"
#include "../../Graphics/Camera/Camera.h"

#include "../../Resources/Image/BMP/BMP.h"
#include "../../Resources/Image/BMP/BMPLoader.h"

#include "../../Resources/Font/FNT/FNT.h"
#include "../../Resources/Font/FNT/FNTLoader.h"
#include "../../Resources/Image/Image.h"

namespace BF
{
	class RenderSystem
	{
	private:
		Camera* _targetCamera;

		glm::mat4 _model = glm::mat4(1.0f);
		glm::mat4 _modelView;
		glm::mat4 _invModelView;
		glm::mat4 _completematrix;

		int _shaderID;
		int _modelViewProjectionID;
		int _inverseModelViewID;
		int _modelViewID;
		int _textureID;	

		FNT _front;
		BMP _texture;
		//PixelArray _pixelArray;

		//--------------------------------
		RenderDataCache* _dataCache;
		unsigned int _bufferID;
		unsigned int _indiceBuffer;
		unsigned int _vertexArrayObjectID;
		//--------------------------------

		Player* _currentPlayer;

	public:
		RenderSystem(Player* player);

		void RenderScene();
		void AddShader(ShaderFile shaderFile);


		void RegisterRenderModel(Model* renderModel);
		int UnRegisterRenderModel(Model* renderModel);

		int RegisterImage(Image* image);
	};
}