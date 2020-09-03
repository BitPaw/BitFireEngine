#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "CameraSettings.h"
#include "../CameraMode.h"
#include "../../Mathmatic/Geometry/Position.h"
#include "../../Mathmatic/Geometry/Direction.h"
#include "../../Mathmatic/Geometry/Rotation.h"

class Camera
{
protected:
	float GetViewSpeed();
	float GetWalkSpeed();

public:
	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProjection;
	glm::vec3 _position;

	CameraSettings* Settings;
	Position* CurrentPosition;
	float WalkSpeed;
	float ViewSpeed;

	Camera();
	Camera(CameraSettings* settings);
	~Camera();

	virtual void Move(Direcion direction);
	virtual void Update();

	glm::mat4 GetUpdatedViewProjection()
	{
		Update();

		return _viewProjection;
	}
};