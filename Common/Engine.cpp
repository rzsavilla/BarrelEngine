#include <stdafx.h>
#include "Engine.h"

Engine::Engine()
{
	this->i = 22;
}

Engine::~Engine()
{

}

template <class Mutex> class lock_guard;

std::shared_ptr<Engine>& Engine::getInstance()
{
	static std::shared_ptr<Engine> instance = nullptr;

	if (!instance)
	{
		if (!instance) {
			instance.reset(new Engine());
		}
	}

	return instance;
}

void Engine::update(float dt)
{

}



