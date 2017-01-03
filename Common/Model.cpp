#include "stdafx.h"
#include "Model.h"

#include <../glm/gtc/type_ptr.hpp>

void Model::setBuffers()
{
	gl::BindVertexArray(VAO);

	//Place data in buffers
	// Vertex position
	//Use expanded vertices and texture coordinates if it has a texture

	if (m_Texture) {
		int www;
		www = 1;
	}
	if (!mesh->getExpandedTexCoords().empty()) {
		int ttt;
		ttt = 1;
	}



	if (!mesh->getExpandedTexCoords().empty() && m_Texture) {
		//Expanded Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getExpandedVertices().size()) * sizeof(GLfloat), mesh->getExpandedVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		//Expanded Texture Coordinates
		gl::BindBuffer(gl::ARRAY_BUFFER, EBO);
		gl::BufferData(gl::ARRAY_BUFFER, mesh->getExpandedTexCoords().size() * sizeof(GLfloat), mesh->getExpandedTexCoords().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);
	}
	//Use Element Array buffer (Indices) 
	else {
		//Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getVertices().size()) * sizeof(GLfloat), mesh->getVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		// Indices
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, EBO);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (mesh->getVertIndices().size()) * sizeof(GLfloat), mesh->getVertIndices().data(), gl::STATIC_DRAW);
	}
	
	gl::BindVertexArray(0);		//Unbind
}

void Model::setMesh(Mesh * newMesh, Texture* newTexture)
{
	mesh = newMesh;
	m_Texture = newTexture;
	setBuffers();
}

void Model::setTexture(Texture* texture)
{
	m_Texture = texture;
	setBuffers();
}

void Model::setPosition(glm::vec3 newPos)
{
	t = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		newPos.x, newPos.y, newPos.z, 1.0f
	);
}

void Model::setScale(glm::vec3 newScale)
{
	s = glm::mat4(
		newScale.x, 0.0f, 0.0f, 0.0f,
		0.0f, newScale.y, 0.0f, 0.0f,
		0.0f, 0.0f, newScale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Model::setRotation(float degrees, Axis axis)
{
	float rad = glm::radians(degrees);
	switch (axis)	//Choose axis to rotate around
	{
	case xAxis:
		r = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(rad), -sin(rad), 0.0f,
			0.0f, sin(rad), cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case yAxis:
		r = glm::mat4(
			cos(rad), 0.0f, sin(rad), 0.0f,
			0, 1.0, 0.0f, 0.0f,
			-sin(rad), 0.0f, cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case zAxis:
		r = glm::mat4(
			cos(rad), -sin(rad), 0.0f, 0.0f,
			sin(rad), cos(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	default:
		break;
	}
}

void Model::translate(glm::vec3 translate)
{
	t *= glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	);
}

void Model::setOrigin(glm::vec3 newOrigin)
{
	origin = newOrigin;
}

void Model::rotate(float degrees, Axis Axis)
{
	float rad = glm::radians(degrees);
	switch (Axis)	//Choose axis to rotate around
	{
	case xAxis:
		r *= glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(rad), -sin(rad), 0.0f,
			0.0f, sin(rad), cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case yAxis:
		r *= glm::mat4(
			cos(rad), 0.0f, sin(rad), 0.0f,
			0, 1.0, 0.0f, 0.0f,
			-sin(rad), 0.0f, cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case zAxis:
		r *= glm::mat4(
			cos(rad), -sin(rad), 0.0f, 0.0f,
			sin(rad), cos(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	default:
		break;
	}
}

Model::Model()
{
	//Generate Buffer handles
	gl::GenVertexArrays(1, &VAO);

	gl::GenBuffers(1, &VBO);
	gl::GenBuffers(1, &EBO);

	 t = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	//Rotate around Y axis
	 r = glm::mat4(
		cos(0), 0.0f, sin(0), 0.0f,
		0, 1.0, 0.0f, 0.0f,
		-sin(0), 0.0f, cos(0), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	s = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Model::draw(GLuint shader, QuatCamera* cam)
{
	//Transform
	glm::mat4 M;	//Model matrix

	glm::mat4 o,oM;
	//Origin matrix to move vertices to origin
	o = glm::mat4(								
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		origin.x, origin.y, origin.z, 1.0f
	);
	//Origin minus matrix to move vertices to 0;
	oM = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-origin.x, -origin.y, -origin.z, 1.0f
	);

	GLint originMatrixID = gl::GetUniformLocation(shader, "mOrigin");
	GLint originMinusMatrixID = gl::GetUniformLocation(shader, "mOriginMinus");
	GLint translateMatrixID = gl::GetUniformLocation(shader, "mTranslate");
	GLint rotateMatrixID = gl::GetUniformLocation(shader, "mRotate");
	GLint scaleMatrixID = gl::GetUniformLocation(shader, "mScale");

	GLint viewMatrixID = gl::GetUniformLocation(shader, "mView");
	GLint projectionMatrixID = gl::GetUniformLocation(shader, "mProjection");
	glm::mat4 V = cam->view();
	gl::UniformMatrix4fv(originMatrixID, 1, gl::FALSE_, glm::value_ptr(o));
	gl::UniformMatrix4fv(originMinusMatrixID, 1, gl::FALSE_, glm::value_ptr(oM));
	gl::UniformMatrix4fv(translateMatrixID, 1, gl::FALSE_, glm::value_ptr(M));
	gl::UniformMatrix4fv(rotateMatrixID, 1, gl::FALSE_, glm::value_ptr(r));
	gl::UniformMatrix4fv(scaleMatrixID, 1, gl::FALSE_, glm::value_ptr(s));

	gl::UniformMatrix4fv(viewMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->view()));
	gl::UniformMatrix4fv(projectionMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->projection()));
	
	// Draw mesh
	

	//Has Texture
	if (!mesh->getExpandedTexCoords().empty() && !m_Texture == NULL) {
		gl::BindVertexArray(this->VBO);
		gl::BindTexture(gl::TEXTURE_2D, m_Texture->object());					//Bind Texture
		gl::DrawArrays(gl::TRIANGLES, 0, mesh->getExpandedVertices().size());
	}
	else {
		gl::BindVertexArray(this->VAO);
		gl::DrawElements(gl::TRIANGLES, mesh->getVertIndices().size(), gl::UNSIGNED_INT, 0);
	}

	gl::BindTexture(gl::TEXTURE_2D, 0);										//Unbind Texture
	gl::BindVertexArray(0);													//Unbind VAO
}