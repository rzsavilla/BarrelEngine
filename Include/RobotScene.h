#pragma once
#include <stdafx.h>

class RobotScene : public Scene {
private:
	int width, height;
	GLuint vboHandles[3];

	GLuint vaoHandle;
	GLuint programHandle;

	void linkMe(GLint vertShader, GLint fragShader);
	GLuint indexSize;
	GLuint numberOfIndices;
	GLuint indices;

	glm::mat4 M;	//Model matrix
	glm::mat4 V;	//View matrix
	glm::mat4 P;	//Projection matrix

	float rot = 0;

public:
	RobotScene();
	void initScene();
	void update(float t);
	void render();
	void resize(int, int);
};