#pragma once

#include <GLM/glm.hpp>
#include <GLM\ext\matrix_transform.hpp>

#include "RenderDataCache.h"

#include "../Window/Window.h"
#include "../Shader/System/ShaderFile.h"
#include "../Shader/System/ShaderLoader.h"
#include "../../Graphics/Camera/Camera.h"
#include "../../Resources/Image/BitMap/BitMap.h"
#include "../../Resources/Font/BitMapFont/BitMapFont.h"
#include "../../Graphics/Model/RectangleModel.h"
#include "../../Resources/Image/PixelArray/PixelArray.h"
#include "../../Resources/Font/BitMapFont/BitMapFontLoader.h"
#include "../../Resources/Image/BitMap/BitMapLoader.h"
#include "../../Resources/Model/WaveFront/WaveFrontLoader.h"
#include "../../Graphics/Model/TriangleModel.h"
#include "../../Player/Player.h"


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

	BitMapFont _front;
	BitMap _texture;
	PixelArray _pixelArray;
	RenderModel model;


	//--------------------------------
	RenderDataCache* _dataCache;
	unsigned int _bufferID;
	unsigned int _indiceBuffer;
	unsigned int _vertexArrayObjectID;
	//--------------------------------

	Player* _currentPlayer;

	void UpdateGPUCache();
	void AllocateGPUCache();
	void AddMesh(Mesh* mesh);
	void UpdateMesh(Mesh* mesh);

public:
	RenderSystem(Player* player);

	void RenderScene();
	void AddShader(ShaderFile shaderFile);
	
	int RegisterRenderModel(RenderModel* renderModel);
	int UnRegisterRenderModel(RenderModel* renderModel);
};