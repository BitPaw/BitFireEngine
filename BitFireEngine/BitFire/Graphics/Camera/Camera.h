#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "CameraSettings.h"

#include "../../Mathematic/Geometry/Position.hpp"
#include "../../Mathematic/Geometry/Direction.h"

#include "../../System/GameTickData.h"

namespace BF
{
	class Camera
	{
		protected:
		float _walkSpeed;
		float _viewSpeed;

		public:
		glm::mat4 _projection;
		glm::mat4 _view;
		glm::mat4 _viewProjection;
		glm::vec3 _position;

		CameraSettings* Settings;
		Position<float> CurrentPosition;

		Camera();
		Camera(CameraSettings* settings);

		void UpdateSystemLink();

		virtual void Move(Direcion direction);
		virtual void Update(GameTickData gameTickData);

		glm::mat4 GetUpdatedViewProjection()
		{
			return _viewProjection;
		}
	};
}