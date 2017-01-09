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

glm::vec3 Transformable::getPosition()
{
	return glm::vec3();
}
