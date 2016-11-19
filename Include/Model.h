#pragma once
#include "stdafx.h"
#include "Camera.h"

/* http://learnopengl.com/#!Model-Loading/Mesh */

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Colour;
};

class Model {
private:
	//Render Data
	GLuint VAO, VBO, EBO;

	glm::mat4 t, r, s;	//Translation,rotation and scale matrix;
	
public:
	Model();
	//Data
	void set();
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	void draw(GLuint shader,Camera* cam);
};