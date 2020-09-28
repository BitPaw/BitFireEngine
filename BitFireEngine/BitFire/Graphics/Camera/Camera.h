#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "CameraSettings.h"
#include "../../Time/TimeCollection.h"
#include "../../Mathematic/Geometry/Position.h"
#include "../../Mathematic/Geometry/Direction.h"

class Camera
{
protected:
	float GetViewSpeed();
	float GetWalkSpeed();
	float _deltaTime;

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
	void SetDeltaTime(float delteTime);

	glm::mat4 GetUpdatedViewProjection()
	{
		Update();

		return _viewProjection;
	}
};