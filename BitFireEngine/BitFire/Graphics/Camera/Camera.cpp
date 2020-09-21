#include "Camera.h"


float Camera::GetViewSpeed()
{
	return ViewSpeed * TimeCollection::DeltaTime * 10000;
}

float Camera::GetWalkSpeed()
{
	return WalkSpeed * TimeCollection::DeltaTime * 500;
}

Camera::Camera() : Camera(new CameraSettings(1, 1))
{
	
}

Camera::Camera(CameraSettings* settings)
{
	_position = glm::vec3(0.0f);
	_view = glm::mat4(1.0f);

	Settings = settings;
	CurrentPosition = new Position();

	WalkSpeed = 0.01f;
	ViewSpeed = 0.03f;

	Update();
}

Camera::~Camera()
{
//	delete Settings;
//	delete CurrentPosition;
}

void Camera::Move(Direcion direction)
{
	glm::vec3 movement;
	float movementSpeed = GetWalkSpeed();

	switch (direction)
	{
	case Direcion::Up:
		movement = glm::vec3(0, movementSpeed, 0);
		break;

	case Direcion::Down:
		movement = glm::vec3(0, -movementSpeed, 0);
		break;

	case Direcion::Left:
		movement = glm::vec3(-movementSpeed, 0, 0);
		break;

	case Direcion::Right:
		movement = glm::vec3(movementSpeed, 0, 0);
		break;

	case Direcion::Forward:
		movement = glm::vec3(0, 0, -movementSpeed);
		break;

	case Direcion::Backward:
		movement = glm::vec3(0, 0, movementSpeed);
		break;
	}

	_position += movement;

	_view =  glm::translate(_view, movement * (-1.0f));
}

void Camera::Update()
{
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

void Camera::SetDeltaTime(float delteTime)
{
	_deltaTime = delteTime;
}
