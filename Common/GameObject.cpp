#include <stdafx.h>
#include "GameObject.h"

#include <Transformable.h>

GameObject::GameObject() {

}

void GameObject::attachComponent(ComponentPtr newComponent)
{
	m_ptrComponents.push_back(std::move(newComponent));
	m_ptrComponents.at(0)->init();

	std::cout << "Attached\n";
}