#include "stdafx.h"
#include "Camera.h"
#include <../glm/gtc/matrix_transform.hpp>

Camera::Camera() {

}

Camera::Camera(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane)
{
	FOV = FieldOfView;
	Aspect = AspectRatio;
	Near = NearPlane;
	Far = FarPlane;
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
