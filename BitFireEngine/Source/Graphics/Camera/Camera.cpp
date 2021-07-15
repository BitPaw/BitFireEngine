#include "Camera.h"
#include "../../../../ResourceSystem/Source/Math/Geometry/Direction.h"
#include <stdio.h>

//#include "../../System/GameSystem.h"

BF::Camera::Camera() : Camera(new CameraSettings(1, 1))
{

}

BF::Camera::Camera(CameraSettings* settings)
{
	Settings = settings;
}

void BF::Camera::UpdateSystemLink()
{
	//BF::System.OnGameTick.AddListener([&](GameTickData gameTickData) {Update(gameTickData); });
}

void BF::Camera::Move(Direcion direction)
{
	Vector3<float> movement;
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

	MatrixModel.Move(movement);
}

void BF::Camera::Update(GameTickData gameTickData)
{
	printf("Updated! Camera\n");

	_walkSpeed = gameTickData.GetSmoothDeltaTime() * 500;
	_viewSpeed = gameTickData.GetSmoothDeltaTime() * 10000;

	switch (Settings->Mode)
	{
		case CameraMode::Orthographic:
			MatrixProjection.Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, Settings->Far);
			break;

		case CameraMode::Perspectdive:
			MatrixProjection.Perspective(Settings->FieldOfView, 1.0f, Settings->Near, Settings->Far);
			break;
	}
}