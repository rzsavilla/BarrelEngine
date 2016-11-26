#pragma once
#include "stdafx.h"
#include "Model.h"

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class Robot
{
private:
	char legStates[2];
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	// draws a unit cube
	void DrawCube(glm::vec3 pos, glm::vec3 scale, float rotation, Axis axis, glm::vec3 colour);

	// methods to draw the parts of the robot
	void DrawArm(float xPos, float yPos, float zPos);
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawTorso(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawFoot(float xPos, float yPos, float zPos);

	Camera *cam;
	GLuint shader;

	Model cube;
	Model Head, Torso, LeftLeg, RightLeg, LeftArm, RightArm, LeftFoot, RightFoot;
	glm::vec3 position;
	glm::vec3 heading;
	void initModel();
	void createCube();

	float rot;		//Rotation around y axis
	glm::mat4 rotMatrix;
	float fTurnSpeed = 100.0f;
	float fMoveSpeed =  1.0f;

public:

	Robot();
	virtual ~Robot();

	void setCamera(Camera* cam);
	void setShader(GLuint Shader);

	// draws the entire robot
	void DrawRobot(float xPos, float yPos, float zPos, float rotation);

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void turnLeft();
	void turnRight();

	void setPosition(float x,float y,float z);

	// updates the robot data
	void Prepare(float dt);
};