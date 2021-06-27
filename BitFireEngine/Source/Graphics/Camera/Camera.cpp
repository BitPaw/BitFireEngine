#include "Camera.h"
#include "../../../../MathSystem/Source/Geometry/Direction.h"
#include "../../../../MathSystem/Dependencies/include/glm/glm.hpp"
#include "../../../../MathSystem/Dependencies/include/glm/ext.hpp"

//#include "../../System/GameSystem.h"

BF::Camera::Camera() : Camera(new CameraSettings(1, 1))
{

}



BF::Camera::Camera(CameraSettings* settings)
{
	_position = glm::vec3(0.0f);
	_view = glm::mat4(1.0f);

	Settings = settings;
	CurrentPosition.Set(0,0,0);
}

void BF::Camera::UpdateSystemLink()
{
	//BF::System.OnGameTick.AddListener([&](GameTickData gameTickData) {Update(gameTickData); });
}

void BF::Camera::Move(Direcion direction)
{
	Position<float> movement;
	Vector3 movementGLM;
	float movementSpeed = _walkSpeed;

	switch (direction)
	{
		case Direcion::Up:
			movement.Set(0, movementSpeed, 0);
			break;

		case Direcion::Down:
			movement.Set(0, -movementSpeed, 0);
			break;

		case Direcion::Left:
			movement.Set(-movementSpeed, 0, 0);
			break;

		case Direcion::Right:
			movement.Set(movementSpeed, 0, 0);
			break;

		case Direcion::Forward:
			movement.Set(0, 0, -movementSpeed);
			break;

		case Direcion::Backward:
			movement.Set(0, 0, movementSpeed);
			break;
	}

	_position += movementGLM;
	CurrentPosition.Add(movement);

	movementGLM = Vector3(movement.X, movement.Y, movement.Z);

	_view = glm::translate(_view, movementGLM * (-1.0f));
}

void BF::Camera::Update(GameTickData gameTickData)
{
	printf("Updated! Camera\n");

	_walkSpeed = gameTickData.GetSmoothDeltaTime() * 500;
	_viewSpeed = gameTickData.GetSmoothDeltaTime() * 10000;

	switch (Settings->Mode)
	{
		case CameraMode::Orthographic:
			_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, Settings->Far);
			break;

		case CameraMode::Perspectdive:
			_projection = glm::perspective(glm::radians(Settings->FieldOfView), 1.0f, Settings->Near, Settings->Far);
			break;
	}

	_viewProjection = _projection * _view;
}
