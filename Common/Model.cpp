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
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getExpandedVertices().size()) * sizeof(GLfloat), mesh->getExpandedVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		//Expanded Texture Coordinates
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, mesh->getExpandedTexCoords().size() * sizeof(GLfloat), mesh->getExpandedTexCoords().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);

		//Normals
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getExpandedNormals().size()) * sizeof(GLfloat), mesh->getExpandedNormals().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(2);
	}
	else if (!mesh->getExpandedNormals().empty()) {
		//Expanded Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getExpandedVertices().size()) * sizeof(GLfloat), mesh->getExpandedVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		////Expanded Texture Coordinates
		//gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		//gl::BufferData(gl::ARRAY_BUFFER, mesh->getExpandedTexCoords().size() * sizeof(GLfloat), mesh->getExpandedTexCoords().data(), gl::STATIC_DRAW);
		//gl::VertexAttribPointer((GLuint)1, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		//gl::EnableVertexAttribArray(1);

		//Normals
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, (mesh->getExpandedNormals().size()) * sizeof(GLfloat), mesh->getExpandedNormals().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(2);
	}
	//Use Element Array buffer (Indices) 
	else {
		//Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
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

void Model::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_ptrShader = shader;
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
	scale = newScale;
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

glm::mat4 Model::getTransform()
{
	glm::mat4 translate,rotate,s, o, originMinus;

	translate = t;
	rotate = r;

	o = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		origin.x, origin.y, origin.z, 1.0f
	);

	s = glm::mat4(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	//Scale -> translate to origin -> rotate -> translate to position
	//Translates to origin first in order to cause rotation around that origin
	return t * r * o * s;
}

void Model::rotate(float degrees, Axis Axis)
{
	glm::mat4 s = r;

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

	gl::GenBuffers(3, handle);

	gl::GenBuffers(1, &VBO[0]);
	gl::GenBuffers(1, &VBO[1]);
	gl::GenBuffers(1, &EBO);

	 t = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	 r = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	s = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Model::draw(GLSLProgram* shader)
{
	m_ptrShader->use();	//Ensure correct m_ptrShader is used

	/////////////Model Transform variables///////////////////
	//Transform
	glm::mat4 M(1.0f);	//Model matrix

	glm::mat4 o,oM;

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

	s = glm::mat4(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	//Pass Uniform model transform variables to m_ptrShader program
	m_ptrShader->setUniform("mOrigin", o);
	m_ptrShader->setUniform("mOriginMinus", oM);
	m_ptrShader->setUniform("mTranslate", t);
	m_ptrShader->setUniform("mRotate", r);
	m_ptrShader->setUniform("mScale", s);

	m_ptrShader->setUniform("mModel", getTransform());
	///////////Draw Model////////////////////////
	//Has Texture
	if ((!mesh->getExpandedTexCoords().empty() && !m_Texture == NULL)) {
		gl::BindVertexArray(this->VAO);
		gl::BindTexture(gl::TEXTURE_2D, m_Texture->object());					//Bind Texture
		gl::DrawArrays(gl::TRIANGLES, 0, mesh->getExpandedVertices().size());
									
	}
	else if (!mesh->getExpandedNormals().empty()) {
		gl::BindVertexArray(this->VAO);
		gl::DrawArrays(gl::TRIANGLES, 0, mesh->getExpandedVertices().size());
	}
	else {
		gl::BindVertexArray(this->VAO);
		gl::DrawElements(gl::TRIANGLES, mesh->getVertIndices().size(), gl::UNSIGNED_INT, 0);
	}
	gl::BindVertexArray(0);													//Unbind VAO
	gl::BindTexture(gl::TEXTURE_2D, 0);										//Unbind Texture				
}