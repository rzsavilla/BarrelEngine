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
	GLint modelMatrixID = gl::GetUniformLocation(shader, "mModel");
	GLint viewMatrixID = gl::GetUniformLocation(shader, "mView");
	GLint projectionMatrixID = gl::GetUniformLocation(shader, "mProjection");

	gl::UniformMatrix4fv(modelMatrixID, 1, gl::FALSE_, glm::value_ptr(M));
	gl::UniformMatrix4fv(viewMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->getView()));
	gl::UniformMatrix4fv(projectionMatrixID, 1, gl::FALSE_, glm::value_ptr(cam->getPerspective()));

	// Draw mesh
	gl::BindVertexArray(this->VAO);
	gl::DrawElements(gl::TRIANGLES, this->indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);
}