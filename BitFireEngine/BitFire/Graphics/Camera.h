#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "../Mathmatic/Geometry/Position.h"
#include "CameraSettings.h"

class Camera
{
private:
	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProjection;

public:
	CameraSettings* Settings;
	Position* CurrentPosition;

	Camera();
	Camera(CameraSettings* settings);
	~Camera();

	void Move(glm::vec3 vector);
	void Update();

	glm::mat4 GetUpdatedViewProjection()
	{
		Update();

		return _viewProjection;
	}
};