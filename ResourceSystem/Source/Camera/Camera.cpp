#include "Camera.h"
#include <stdio.h>

float BF::Camera::GetAspectRatio()
{
	return Width / Height;
}

BF::Camera::Camera()
{
	_walkSpeed = 0.3;
	_viewSpeed = 2.5;

	FieldOfView = 90;
	Height = 1000;
	Width = 1000;
	Near = 0.01;
	Far = -1;

	Perspective = CameraPerspective::Perspective;

	CurrentRotation.Set(0, 0, 0);
	_up.Set(0.0f, 1.0f, 0.0f);

	switch (Perspective)
	{
		case CameraPerspective::Orthographic:
			MatrixProjection.Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, Near, Far);
			break;

		case CameraPerspective::Perspective:
			MatrixProjection.Perspective(FieldOfView, GetAspectRatio(), Near, Far);
			break;
	}
}

void BF::Camera::Rotate(float x, float y)
{
	const float maxValue = 85.0f;
	const float minValue = -85.0f;
	float movementSpeed = _viewSpeed;

	CurrentRotation.X -= x * movementSpeed;
	CurrentRotation.Y += y * movementSpeed;

	// Cap
	if (CurrentRotation.Y > maxValue)
	{
		CurrentRotation.Y = maxValue;
	}

	if (CurrentRotation.Y < minValue)
	{
		CurrentRotation.Y = minValue;
	}

	float pitchRAD = glm::radians(CurrentRotation.Y);
	float yawRAD = glm::radians(CurrentRotation.X);


	float rx = cos(pitchRAD) * cos(yawRAD);
	float ry = sin(pitchRAD);
	float rz = cos(pitchRAD) * sin(yawRAD);

	_lookAt.Set(rx, ry, rz);
	_lookAt.Normalize();
}

void BF::Camera::Move(Direcion direction)
{
	Vector3<float> movement;
	float movementSpeed = _walkSpeed;

	switch (direction)
	{
		case Direcion::Up:
			movement.Set(0, 1, 0);
			break;

		case Direcion::Down:
			movement.Set(0, -1, 0);
			break;

		case Direcion::Left:
			movement.CrossProduct(_lookAt, _up);
			movement.Multiply(-1, 0, -1);
			movement.Normalize();
			break;

		case Direcion::Right:
			movement.CrossProduct(_lookAt, _up);
			movement.Multiply(1, 0, 1);
			movement.Normalize();
			break;

		case Direcion::Forward:
			movement = _lookAt * Vector3<float>(1, 0, 1); // Remove Y movement
			break;

		case Direcion::Backward:
			movement = _lookAt * Vector3<float>(-1, 0, -1);
			break;
	}

	movement *= movementSpeed;

	MatrixModel.Move(movement);
	//MatrixView.Move(movement);
}

void BF::Camera::Update(float deltaTime)
{
	Vector4<float> currentPositionx4 = MatrixModel.CurrentPosition();
	Vector3<float> currentPosition = Vector3<float>(currentPositionx4.Date[0], currentPositionx4.Date[1], currentPositionx4.Date[2]);

	float walkSpeedSmoothed = deltaTime * _walkSpeed;
	float viewSpeedSmoothed = deltaTime * _viewSpeed;

	MatrixView.LookAt(currentPosition, currentPosition + _lookAt, _up);

	Vector3<float> gravity = Vector3<float>(0.f, -0.918f, 0.f);

	MatrixModel.Motion(Force, Velocity, 1, gravity, deltaTime);

	//printf("CurrentPosition <%2.2f %2.2f %2.2f>\n", currentPosition.Data[0], currentPosition.Data[1], currentPosition.Data[2]);
}