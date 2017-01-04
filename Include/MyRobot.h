#pragma once

#include <stdafx.h>
#include "Model.h"

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class MyRobot
{
private:
	char legStates[2];
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	Model Head, Torso, ArmLeft, ArmRight, LegLeft, LegRight, FootLeft, FootRight;
	void initModel(Mesh* CubeMesh);

	bool m_bForwards;
	bool m_bBackwards;
	bool m_bAnimate;

	glm::vec3 m_vPosition;		//!< Currrent Position
	glm::vec3 m_vDirection;		//!< Direction vector
	float m_fRotationY;			//!< Heading/Facing/Orientation
	float m_fTurnSpeed;			//!< How quickly the robot can turn
	float m_fMoveSpeed;			//!< How quickly the robot moves towards its heading
	float m_fAnimationSpeed;	//!< Animation speed

	glm::mat4 m_orientationMatrix;
	glm::mat4 m_translateMatrix;
	glm::vec3 m_Velocity;

	// updates the robot data
	void animate(float dt);
public:
	MyRobot(Mesh* CubeMesh); //!< Default Constructor
	virtual ~MyRobot();		 //!< Destructor

	void turnLeft();		//!< Rotates robot to the left
	void turnRight();		//!< Rotates robot to the right
	void moveForward();		//!< Moves robot towards facing
	void moveBackward();	//!< Moves robot back


	void setMoveSpeed(float newSpeed);
	void setTurnSpeed(float newTurnSpeed);

	void update(const float dt);

	// draws the entire robot
	void draw(GLSLProgram* shader);

	
};
