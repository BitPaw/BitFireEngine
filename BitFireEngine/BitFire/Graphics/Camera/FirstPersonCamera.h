#pragma once

#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "../../Mathematic/Geometry/Rotation.h"

namespace BF
{
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
}