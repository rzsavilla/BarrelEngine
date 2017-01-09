#pragma once

#include <stdafx.h>
#include "Component.h"

typedef std::unique_ptr<Component> ComponentPtr;

class GameObject {
private:
	unsigned int m_uiHandle;		//Object index
	std::vector<std::unique_ptr<Component>> m_ptrComponents;	//!< Stores all components object has.
public:
	
	GameObject();	//!< Default constructor
	void attachComponent(ComponentPtr newComponent);
};