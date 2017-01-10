#include <stdafx.h>
#include "Transformable.h"

Transformable::Transformable()
{

}

void Transformable::init()
{
	glm::vec3 m_vPosition = glm::vec3(0.0f);
	std::cout << "HEllo\n";
}

void Transformable::update(float dt)
{

}

void Transformable::sendMessage(const Message & msg)
{

}

void Transformable::move(glm::vec3 vector)
{
	m_vPosition += vector;
}

void Transformable::rotate(glm::vec3 vector)
{
	m_vRotation += vector;
}

void Transformable::scale(glm::vec3 vector)
{
	m_vScale += vector;
}

void Transformable::rotateX(float x)
{
	m_vRotation.x = x;
}

void Transformable::rotateY(float y)
{
	m_vRotation.y = y;
}

void Transformable::rotateZ(float z)
{
	m_vRotation.z = z;
}

void Transformable::setPosition(const glm::vec3 newPosition)
{
	m_vPosition = newPosition;
}

void Transformable::setRotation(const glm::vec3 newRotation)
{
	m_vRotation = newRotation;
}

void Transformable::setOrigin(const glm::vec3 newOrigin)
{
	m_vOrigin = newOrigin;
}

void Transformable::setScale(const glm::vec3 newScale)
{
	m_vScale = newScale;
}

void Transformable::setScale(const float newScale)
{
	m_vScale = glm::vec3(newScale, newScale, newScale);
}

void Transformable::setPosition(const float x, const float y, const float z)
{
	m_vPosition = glm::vec3(x, y, z);
}

void Transformable::setRotation(const float x, const float y, const float z)
{
	m_vRotation = glm::vec3(x, y, z);
}

void Transformable::setOrigin(const float x, const float y, const float z)
{
	m_vRotation = glm::vec3(x, y, z);
}

void Transformable::setScale(const float x, const float y, const float z)
{
	m_vScale = glm::vec3(x, y, z);
}

glm::vec3 Transformable::getPosition()
{
	return m_vPosition;
}

glm::vec3 Transformable::getRotation()
{
	return m_vRotation;
}

glm::vec3 Transformable::getOrigin()
{
	return m_vOrigin;
}

glm::mat4 Transformable::getTransform()
{
	float fRadianX = glm::radians(m_vRotation.x);		//Convert rotation angles to radianss
	float fRadianY = glm::radians(m_vRotation.y);
	float fRadianZ = glm::radians(m_vRotation.z);
	//Rotation on the X axis
	glm::mat4 mRotationX(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, glm::cos(fRadianX), -glm::sin(fRadianX), 0.0f),
		glm::vec4(0.0f, glm::sin(fRadianX), glm::cos(fRadianX), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	//Rotation on the Y axis
	glm::mat4 mRotationY(
		glm::vec4(glm::cos(fRadianX), 0.0f, glm::sin(fRadianX), 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(-glm::sin(fRadianX), 0.0f, glm::cos(fRadianX), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	//Rotation on the Z axis
	glm::mat4 mRotationZ(
		glm::vec4(glm::cos(fRadianY), -glm::sin(fRadianY), 0.0f, 0.0f),
		glm::vec4(glm::sin(fRadianY), glm::cos(fRadianY), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	//Translation matrix
	glm::mat4 mTranslate(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.0f)
	);
	//Origin translation matrix
	glm::mat4 mOrigin(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(m_vOrigin.x, m_vOrigin.y, m_vOrigin.z, 1.0f)
	);
	//Scale matrix
	glm::mat4 mScale(
		glm::vec4(m_vScale.x, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, m_vScale.y, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, m_vScale.z, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	//Scale -> translate to origin -> rotate -> translate to position
	//Translates to origin first in order to cause rotation around that origin
	return mTranslate * mRotationX * mRotationY * mRotationZ * mOrigin * mScale;
}
