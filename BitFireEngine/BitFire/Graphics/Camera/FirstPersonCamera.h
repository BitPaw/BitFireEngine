#pragma once

#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "../../Mathematic/Geometry/Position.hpp"

namespace BF
{
	class FirstPersonCamera : public Camera
	{
	private:
		glm::vec3 _up;
		glm::vec3 _lookAt;

		int _modelViewProjectionID;
		int _inverseModelViewID;
		int _modelViewID;
		int _textureID;
		glm::mat4 _modelView;
		glm::mat4 _invModelView;
		glm::mat4 _completematrix;

		bool ValidShader;

	public:
		Position<float> CurrentRotation;

		void FetchGPUReferences(unsigned int shaderID);

		void Rotate(float x, float y);
		void Update(GameTickData gameTickData) override;
		void Move(Direcion direction) override;

		FirstPersonCamera();
	};
}