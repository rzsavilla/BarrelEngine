#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "QuatCamera.h"
#include "Texture.h"
#include "GLSLProgram.h"
#include "ID.h"

/* http://learnopengl.com/#!Model-Loading/Mesh */

enum Axis { xAxis, yAxis, zAxis };

class Model : public ID {
private:
	//Render Data
	GLuint VAO, VBO[2], EBO;

	GLuint handle[3];

	glm::vec3 scale;

	std::shared_ptr<GLSLProgram> m_ptrShader;
	glm::mat4 t, r, s;	//Translation,rotation and scale matrix;
	glm::vec3 origin;	
	Mesh* mesh;	//!< Store points to mesh model data
	Texture* m_Texture;	//!< Points to texture
	Material* m_Material;
	void setBuffers(); //!< Pass mesh data to OpenGL buffers
public:
	Model();									/*!< Default Constructor */

	void setMesh(Mesh * newMesh,Texture* newTexture = NULL);
	void setMaterial(Material* material);
	void setTexture(Texture* texture);
	void setShader(std::shared_ptr<GLSLProgram> shader);
	
	void setPosition(glm::vec3 newPos);			/*!< Set model position */
	void setScale(glm::vec3 newScale);			/*!< Set model scale */
	void setRotation(float degrees, Axis axis); /*!< Set model rotation on choosen axis */
	void setOrigin(glm::vec3 newOrigin);		/*!< Set models origin*/

	glm::mat4 getTransform();					//!< Returns model transformation matrix ;


	std::shared_ptr<GLSLProgram> getShader();

	void translate(glm::vec3 translate);		/*!< Move model */
	void rotate(float degrees, Axis Axis);		/*!< Rotate model */
	void draw();				/*!< Draw model */
};