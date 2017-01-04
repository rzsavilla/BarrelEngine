#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "QuatCamera.h"
#include "Texture.h"
#include "GLSLProgram.h"

/* http://learnopengl.com/#!Model-Loading/Mesh */

enum Axis { xAxis, yAxis, zAxis };

class Model {
private:
	//Render Data
	GLuint VAO, VBO, EBO;

	glm::vec3 scale;


	glm::mat4 t, r, s;	//Translation,rotation and scale matrix;
	glm::vec3 origin;	
	Mesh* mesh;	//!< Store points to mesh model data
	Texture* m_Texture;	//!< Points to texture

	void setBuffers(); //!< Pass mesh data to OpenGL buffers
public:
	Model();									/*!< Default Constructor */

	void setMesh(Mesh * newMesh,Texture* newTexture = NULL);				
	void setTexture(Texture* texture);
	
	void setPosition(glm::vec3 newPos);			/*!< Set model position */
	void setScale(glm::vec3 newScale);			/*!< Set model scale */
	void setRotation(float degrees, Axis axis); /*!< Set model rotation on choosen axis */
	void setOrigin(glm::vec3 newOrigin);		/*!< Set models origin*/

	void translate(glm::vec3 translate);		/*!< Move model */
	void rotate(float degrees, Axis Axis);		/*!< Rotate model */
	void draw(GLSLProgram* shader);		/*!< Draw model */
};