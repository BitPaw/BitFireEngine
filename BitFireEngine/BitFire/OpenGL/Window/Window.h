#pragma once

#ifndef BF_Window
#define BF_Window

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "../Shader/System/ShaderFile.h"
#include "../Shader/System/ShaderLoader.h"
#include "../../IO/InputContainer.h"
#include "../../Graphics/Camera/FirstPersonCamera.h"
#include "../../Mathematic/Interpolate.h"
#include "../../Mathematic/Geometry/Direction.h"
#include "../../Time/TimeCollection.h"
#include "../../Graphics/RenderModel.h"
#include "../Buffer/VertexBuffer.h"
#include "../../Resources/Model/WaveFront/WaveFrontLoader.h"
#include "../../Graphics/Model/RectangleModel.h"
#include "../../Graphics/Model/TriangleModel.h"
#include "../../Resources/Image/BitMap/BitMapLoader.h"
#include "../../Resources/Font/BitMapFont/BitMapFont.h"

class Window
{
private:
	static Window* _instance;

	FirstPersonCamera _camera;
	GLFWwindow* _window;

	void UpdateInput();

	int shader;

	int _modelViewProjectionID;
	int _inverseModelViewID;
	int _modelViewID;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 modelView;
	glm::mat4 invModelView;

	glm::mat4 completematrix;

	RenderModel _renderModel;
	PixelArray pixelarray;
	BitMap boxTexture;
	BitMapFont font;

	unsigned int _models;
	VertexBuffer buffer;



public:
	static Window* GetInstance();
	InputContainer Input;	

	Window();
	Window(const int width, const int height, const char* title);
	~Window();
	bool Exit;

	// Window Utility	
	void ResizeWindow(const int width, const int height);

	bool Create(const int width, const int height, const char* title);
	void Update();
	void SetShader(ShaderFile shaderFile);
};
#endif 