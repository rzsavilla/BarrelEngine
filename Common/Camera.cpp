#include "stdafx.h"
#include "Camera.h"
#include <../glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	eye = glm::vec3(0.0f, 0.0f, 1.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	FOV = 0.0f;
	Aspect = 0.0f;
	Near = 0.1f;
	Far = 100.0f;
}

Camera::Camera(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane)
{
	FOV = FieldOfView;
	Aspect = AspectRatio;
	Near = NearPlane;
	Far = FarPlane;

	eye = glm::vec3(0.0f, 0.0f, 1.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::setPosition(glm::vec3 newPosition)
{
	eye = newPosition;
}

void Camera::setFacing(glm::vec3 newFacing)
{
	center = newFacing;
}

void Camera::setUpVector(glm::vec3 newUp)
{
	up = newUp;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(eye, center, up);
}

glm::mat4 Camera::getPerspective()
{
	return glm::perspective(glm::radians(FOV), Aspect, Near, Far);
}
