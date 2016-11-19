#pragma once

#include "stdafx.h"

class Camera {
private:
	glm::vec3 eye;		//Position
	glm::vec3 center;	//Camera facing
	glm::vec3 up;		//Up vector

	float FOV;		//Field of view (degrees)
	float Aspect;	//Aspect Ratio
	float Near;		//Near plane
	float Far;		//Far plane
public:
	Camera();
	Camera(float FOV, float Aspect, float NearPlane,float FarPlane);

	void setPosition(glm::vec3 newPosition);
	void setFacing(glm::vec3 newFacing);
	void setUpVector(glm::vec3 newUp);

	//Return view matrix
	glm::mat4 getView();

	//Return perspective matrix
	glm::mat4 getPerspective();
};