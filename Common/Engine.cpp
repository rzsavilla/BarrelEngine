#include <stdafx.h>
#include "Engine.h"

Engine::Engine()
{

}

void Engine::handleMessages()
{
	//Iterate through components
	for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {

		//Send messages to components
		for (int i = 0; i < m_vMessages.size(); i++) {
			(*it)->handleMessage(m_vMessages.at(i)); //Components will handle the messages
		}
	}

	//Engine reads messages
	std::string s;
	for (int i = 0; i < m_vMessages.size(); i++) {
		s = m_vMessages.at(i)->sID;
		if (s == "Scene_Exit") {
			m_bRunning = false;
		}
	}

	m_vMessages.clear();		//Remove all messages
	
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

void Engine::init()
{
	m_bRunning = true;

	//Initialize attached components
	for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			(*it)->init();
	}

	handleMessages();
}

void Engine::run()
{
	float f = 0;
	float fOld = 0;
	while (m_bRunning) {
		f = (float)glfwGetTime();
		float dt = f - fOld;
		fOld = f;

		handleMessages();	//Pass messages to components
		//Update components
		for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			(*it)->update(dt);
		}

		//std::cout << dt << "\n";
	}
}