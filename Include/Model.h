#pragma once
#include "stdafx.h"
#include "Camera.h"

/* http://learnopengl.com/#!Model-Loading/Mesh */

enum Axis { xAxis, yAxis, zAxis };

class Vertex {
public:
	Vertex();
	Vertex(glm::vec3 pos, glm::vec3 colour);
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

	
	void setPosition(glm::vec3 newPos); /*!< Set model position */
	void setScale(glm::vec3 newScale);	/*!< Set model scale */
	void setRotation(float degrees, Axis axis); /*!< Set model rotation on choosen axis */

	void translate(glm::vec3 translate);			/*!< Move model */
	void rotate(float degrees, Axis Axis);	/*!< Rotate model */
	void setColour(glm::vec3 newColour); /*!< Set the colour of all the models vertices*/
	void draw(GLuint shader,Camera* cam); /*!< Draw model */
};