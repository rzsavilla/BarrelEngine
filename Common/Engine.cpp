#include <stdafx.h>
#include "Engine.h"

Engine::Engine()
{

}

void Engine::gameLoop()
{

}

void Engine::render()
{
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