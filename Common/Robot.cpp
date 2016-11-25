#pragma once
#include "stdafx.h"
#include "Robot.h"

Robot::Robot()
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	initModel();
}

Robot::~Robot()
{

}

void Robot::initModel()
{
	createCube();
	Head = cube;
	Torso = cube;
	LeftArm = cube;
	RightArm = cube;
	LeftLeg = cube;
	RightLeg = cube;
	LeftFoot = cube;
	RightFoot = cube;
}

void Robot::createCube()
{
	//Vertex top, left, right, bot;
	glm::vec3 c = glm::vec3(1.0f, 1.0f, 1.0f);

	cube.vertices.push_back(Vertex(glm::vec3(-0.5, 0.5f, 0.5f), c));	//Top left Front 0
	cube.vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), c));	//Bot Left Front 1
	cube.vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), c));	//Bot Right Front 2
	cube.vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), c));	//Top Right Front 3
	cube.vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), c));  //Top Left Back 4 
	cube.vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), c));	//Bot Left Back 5 
	cube.vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), c));	//Bot Right Back 6 
	cube.vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), c));	//Top Right Back 7

																		//Front Face
	cube.indices.push_back(0);
	cube.indices.push_back(1);
	cube.indices.push_back(2);
	cube.indices.push_back(2);
	cube.indices.push_back(0);
	cube.indices.push_back(3);
	//Right Face
	cube.indices.push_back(3);
	cube.indices.push_back(7);
	cube.indices.push_back(2);
	cube.indices.push_back(7);
	cube.indices.push_back(2);
	cube.indices.push_back(6);
	//Back Face
	cube.indices.push_back(6);
	cube.indices.push_back(5);
	cube.indices.push_back(4);
	cube.indices.push_back(4);
	cube.indices.push_back(7);
	cube.indices.push_back(6);
	//Bot Face
	cube.indices.push_back(6);
	cube.indices.push_back(5);
	cube.indices.push_back(2);
	cube.indices.push_back(2);
	cube.indices.push_back(5);
	cube.indices.push_back(1);
	//Left Face
	cube.indices.push_back(1);
	cube.indices.push_back(5);
	cube.indices.push_back(4);
	cube.indices.push_back(4);
	cube.indices.push_back(1);
	cube.indices.push_back(0);
	//Top Face
	cube.indices.push_back(0);
	cube.indices.push_back(4);
	cube.indices.push_back(3);
	cube.indices.push_back(3);
	cube.indices.push_back(7);
	cube.indices.push_back(4);

	//Back Face
	cube.indices.push_back(6);
	cube.indices.push_back(4);
	cube.indices.push_back(7);
	cube.indices.push_back(5);
	cube.indices.push_back(2);
	cube.indices.push_back(4);
	cube.indices.push_back(0);
	cube.indices.push_back(1);

	cube.translate(glm::vec3(0.0f, 0.0f, 0.0f));
	cube.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	cube.setRotation(0, Axis::xAxis);

	cube.set();
}


void Robot::setCamera(Camera *camera)
{
	cam = camera;
}

void Robot::setShader(GLuint Shader)
{
	shader = Shader;
}

void Robot::DrawCube(glm::vec3 pos, glm::vec3 scale,float rotation,Axis axis,glm::vec3 colour)
{
	Model cube;
	//Vertex top, left, right, bot;
	glm::vec3 c = colour;

	cube.vertices.push_back(Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), c));	//Top left Front 0
	cube.vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), c));	//Bot Left Front 1
	cube.vertices.push_back(Vertex(glm::vec3(1.0f, -1.0f, 1.0f), c));	//Bot Right Front 2
	cube.vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 1.0f), c));	//Top Right Front 3
	cube.vertices.push_back(Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), c));  //Top Left Back 4 
	cube.vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), c));	//Bot Left Back 5 
	cube.vertices.push_back(Vertex(glm::vec3(1.0f, -1.0f, -1.0f), c));	//Bot Right Back 6 
	cube.vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, -1.0f), c));	//Top Right Back 7

																		//Front Face
	cube.indices.push_back(0);
	cube.indices.push_back(1);
	cube.indices.push_back(2);
	cube.indices.push_back(2);
	cube.indices.push_back(0);
	cube.indices.push_back(3);
	//Right Face
	cube.indices.push_back(3);
	cube.indices.push_back(7);
	cube.indices.push_back(2);
	cube.indices.push_back(7);
	cube.indices.push_back(2);
	cube.indices.push_back(6);
	//Back Face
	cube.indices.push_back(6);
	cube.indices.push_back(5);
	cube.indices.push_back(4);
	cube.indices.push_back(4);
	cube.indices.push_back(7);
	cube.indices.push_back(6);
	//Bot Face
	cube.indices.push_back(6);
	cube.indices.push_back(5);
	cube.indices.push_back(2);
	cube.indices.push_back(2);
	cube.indices.push_back(5);
	cube.indices.push_back(1);
	//Left Face
	cube.indices.push_back(1);
	cube.indices.push_back(5);
	cube.indices.push_back(4);
	cube.indices.push_back(4);
	cube.indices.push_back(1);
	cube.indices.push_back(0);
	//Top Face
	cube.indices.push_back(0);
	cube.indices.push_back(4);
	cube.indices.push_back(3);
	cube.indices.push_back(3);
	cube.indices.push_back(7);
	cube.indices.push_back(4);

	//Back Face
	cube.indices.push_back(6);
	cube.indices.push_back(4);
	cube.indices.push_back(7);
	cube.indices.push_back(5);
	cube.indices.push_back(2);
	cube.indices.push_back(4);
	cube.indices.push_back(0);
	cube.indices.push_back(1);

	cube.translate(pos);
	cube.setScale(scale);
	cube.setRotation(rotation, axis);

	cube.set();

	cube.draw(shader, cam);
}

void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	//glPushMatrix();
	//glColor3f(1.0f, 0.0f, 0.0f);	// red
	//glTranslatef(xPos, yPos, zPos);
	//glScalef(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
	//DrawCube(0.0f, 0.0f, 0.0f);
	//glPopMatrix();

	glm::vec3 colour(1.0f, 0.0f, 0.0f);		// red
	glm::vec3 pos(xPos, yPos, zPos);
	glm::vec3 scale(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
	DrawCube(pos, scale, 0.0f, yAxis, colour);
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glm::vec3 colour(1.0f, 1.0f, 1.0f);	// white
	glm::vec3 pos(xPos, yPos, zPos);
	glm::vec3 scale(2.0f, 2.0f, 2.0f);		// head is a 2x2x2 cube
	Head.setScale(scale);
	Head.translate(pos);
	Head.setColour(colour);
	Head.draw(shader, cam);
}

void Robot::DrawTorso(float xPos, float yPos, float zPos)
{
	glm::vec3 colour(0.0f, 0.0f, 1.0f);		// blue
	glm::vec3 pos(xPos, yPos, zPos);
	glm::vec3 scale(3.0f, 5.0f, 2.0f);		// torso is a 3x5x2 cube
	Torso.setColour(colour);
	Torso.translate(pos);
	Torso.setScale(scale);
	Torso.draw(shader, cam);
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	//glPushMatrix();
	//glTranslatef(xPos, yPos, zPos);

	// draw the foot
	//glPushMatrix();
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//DrawFoot(0.0f, -5.0f, 0.0f);
	//glPopMatrix();

	//glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
	//glColor3f(1.0f, 1.0f, 0.0f);	// yellow
	//DrawCube(0.0f, 0.0f, 0.0f);
	//glPopMatrix();

	//Foot
	glm::vec3 colour(1.0f, 1.0f, 1.0f);		// blue
	glm::vec3 pos(0.0f, -0.5f, 0.0f);
	pos += glm::vec3(xPos, yPos, zPos);
	glm::vec3 scale(0.0f, -5.0f, 0.0f);		
	DrawFoot(pos.x,pos.y-5.0f,pos.z);

	//Foot
	colour = glm::vec3(1.0f, 1.0f, 0.0f);		// yellow
	scale = glm::vec3(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
	pos = glm::vec3(xPos, yPos, zPos);
	DrawCube(pos, scale, 0.0f, yAxis, colour);
}

void Robot::DrawFoot(float xPos, float yPos, float zPos)
{
	//glPushMatrix();
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glTranslatef(xPos, yPos, zPos);
	//glScalef(1.0f, 0.5f, 3.0f);
	glm::vec3 colour(1.0f, 1.0f, 1.0f);		// white
	glm::vec3 pos(xPos, -0.5f + yPos, zPos);
	//pos += glm::vec3(xPos, yPos -0.5f, zPos);
	glm::vec3 scale(1.0f, 0.5f, 3.0f);
	DrawCube(pos, scale, 0.0f, yAxis, colour);
	//glPopMatrix();
}

void Robot::DrawRobot(float xPos, float yPos, float zPos, float rotation)
{
	//glPushMatrix();
	//glTranslatef(xPos, yPos, zPos);	// draw robot at desired coordinates
	//glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	//rot += 0.5f;
	//rotation = rot;

	//position.y += -0.1f;

	Head.setRotation(0, xAxis);
	Torso.setRotation(0, yAxis);
	LeftArm.setRotation(0, yAxis);
	RightArm.setRotation(0, yAxis);
	LeftLeg.setRotation(0, yAxis);
	LeftFoot.setRotation(0, yAxis);
	RightLeg.setRotation(0, yAxis);
	RightFoot.setRotation(0, yAxis);

	Head.rotate(rotation, yAxis);
	Torso.rotate(rotation, yAxis);
	LeftArm.rotate(rotation, yAxis);
	RightArm.rotate(rotation, yAxis);
	LeftLeg.rotate(rotation, yAxis);
	LeftFoot.rotate(rotation, yAxis);
	RightLeg.rotate(rotation, yAxis);
	RightFoot.rotate(rotation, yAxis);

	//// draw head and torso parts
	Head.setPosition(position);
	DrawHead(0.0f, 3.5f, 0.0f);

	Torso.setPosition(position);
	DrawTorso(0.0f, 0.0f, 0.0f);

	// move the left arm away from the torso and rotate it to give "walking" effect
	LeftArm.setPosition(position);
	LeftArm.setOrigin(glm::vec3(-2.0f, -2.0f, 0.5f));
	LeftArm.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	LeftArm.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	//LeftArm.translate(glm::vec3(0.0f, -0.5f, 0.0f));
	LeftArm.rotate(armAngles[LEFT], xAxis);
	LeftArm.translate(glm::vec3(-2.0f, 0.0f, -0.5f));
	LeftArm.draw(shader, cam);

	RightArm.setPosition(position);
	RightArm.setOrigin(glm::vec3(2.0f, -2.0f, 0.0f));
	RightArm.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	RightArm.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	//RightArm.translate(glm::vec3(0.0f, -0.5f, 0.0f));
	RightArm.rotate(armAngles[RIGHT], xAxis);
	RightArm.translate(glm::vec3(2.0f, 0.0f, -0.5f));
	RightArm.draw(shader, cam);
	
	// move the left leg away from the torso and rotate it to give "walking" effect
	//glPushMatrix();
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
	//DrawLeg(-1.0f, -5.0f, -0.5f);
	//glPopMatrix();
	LeftLeg.setPosition(position);
	LeftLeg.setOrigin(glm::vec3(0.0f, -8.0f, 0.0f));
	LeftLeg.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	LeftLeg.setColour(glm::vec3(1.0f, 1.0f, 0.0f));
	//LeftLeg.setRotation(0, xAxis);
	LeftLeg.rotate(legAngles[LEFT], xAxis);
	LeftLeg.translate(glm::vec3(-1.0f, -5.0f, -0.5f));
	LeftLeg.draw(shader, cam);

	LeftFoot.setPosition(position);
	LeftFoot.setScale(glm::vec3(1.0f, 0.5f, 3.0f));
	LeftFoot.translate(glm::vec3(-1.0f, -7.5f, 1.5f));
	LeftFoot.setOrigin(glm::vec3(0.0f, -8.0f, 0.0f));
	//LeftFoot.setRotation(0, xAxis);
	LeftFoot.rotate(legAngles[LEFT], xAxis);
	LeftFoot.draw(shader, cam);

	// move the right leg away from the torso and rotate it to give "walking" effect
	//glPushMatrix();
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	//DrawLeg(1.0f, -5.0f, -0.5f);
	//glPopMatrix();

	RightLeg.setPosition(position);
	RightLeg.setOrigin(glm::vec3(0.0f, -8.0f, 0.0f));
	RightLeg.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	RightLeg.setColour(glm::vec3(1.0f, 1.0f, 0.0f));
	//RightLeg.setRotation(0, xAxis);
	RightLeg.rotate(legAngles[RIGHT], xAxis);
	RightLeg.translate(glm::vec3(1.0f, -5.0f, -0.5f));
	RightLeg.draw(shader, cam);

	RightFoot.setPosition(position);
	RightFoot.setScale(glm::vec3(1.0f, 0.5f, 3.0f));
	RightFoot.translate(glm::vec3(1.0f, -7.0f, 1.5f));
	RightFoot.setOrigin(glm::vec3(0.0f, -8.0f, 0.0f));
	//RightFoot.setRotation(0, xAxis);
	RightFoot.rotate(legAngles[RIGHT], xAxis);
	RightFoot.draw(shader, cam);

	//glPopMatrix();	// pop back to original coordinate system
}

void Robot::Prepare(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 20.0f * dt;
		else
			armAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;

		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 20.0f * dt;
		else
			legAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;
	}
}