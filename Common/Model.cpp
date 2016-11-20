#include "stdafx.h"
#include "Model.h"
#include <../glm/gtc/type_ptr.hpp>

void Model::set()
{
	gl::GenVertexArrays(1, &this->VAO);
	gl::GenBuffers(1, &this->VBO);
	gl::GenBuffers(1, &this->EBO);

	gl::BindVertexArray(this->VAO);
	gl::BindBuffer(gl::ARRAY_BUFFER, this->VBO);

	gl::BufferData(gl::ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, this->EBO);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], gl::STATIC_DRAW);

	// Vertex Positions
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	gl::EnableVertexAttribArray(1);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE_, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Colour));

	gl::BindVertexArray(0);
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

void Model::translate(glm::vec3 translate)
{
	t *= glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	);
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
}

void Model::draw(GLuint shader,Camera* cam)
{
	//Transform
	glm::mat4 M;	//Model matrix
	M = t * r * s;
	GLint modelMatrixID = gl::GetUniformLocation(shader, "mModel");
	GLint viewMatrixID = gl::GetUniformLocation(shader, "mView");
	GLint projectionMatrixID = gl::GetUniformLocation(shader, "mProjection");
	glm::mat4 V = cam->getView();
	gl::UniformMatrix4fv(modelMatrixID, 1, gl::FALSE_, glm::value_ptr(M));
	gl::UniformMatrix4fv(viewMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->getView()));
	gl::UniformMatrix4fv(projectionMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->getPerspective()));

	// Draw mesh
	gl::BindVertexArray(this->VAO);
	//gl::DrawArrays(gl::TRIANGLES, 0, 3);
	gl::DrawElements(gl::TRIANGLES, indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);
}

Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec3 pos, glm::vec3 colour)
{
	Position = pos;
	Colour = colour;
}
