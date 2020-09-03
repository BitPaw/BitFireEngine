#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <GLM/gtx/string_cast.hpp>

#include "Camera.h"

class FirstPersonCamera : public Camera
{
private:
	glm::vec3 _up;
	glm::vec3 _lookAt;

public:
	Rotation CurrentRotation;

	void Rotate(float x, float y);
	void Update() override;
	void Move(Direcion direction) override;

	FirstPersonCamera();

};