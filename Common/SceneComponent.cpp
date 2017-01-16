#include <stdafx.h>
#include "SceneComponent.h"
#include "SceneLoader.h"
#include "Render.h"
#include "Engine.h"

void SceneComponent::handleInput()
{
	m_scenes.at(m_uiActiveScene).second->handleInput(m_ptrWindow);
}

void SceneComponent::init()
{
	//////Initialize OpenGL and create GLFW window
	if (!m_bWindowLoaded) {
		// Initialize GLFW
		if (!glfwInit()) exit(EXIT_FAILURE);

		// Select OpenGL 4.3 with a forward compatible core profile.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, FALSE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 32);

		//Open window
		m_ptrWindow = glfwCreateWindow(1024, 768, "Barrel Engine", NULL, NULL);
		if (m_ptrWindow == NULL) {
			std::cout << "Failed to load window\n";
			system("pause");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(m_ptrWindow);

		//Load OpenGL functions
		gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
		if (!didLoad) {
			//Clean up and abort
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		m_bWindowLoaded = true;

		//Pass GLFW window pointer to components
		m_ptrLocalMessages->push_back(std::make_shared<SetWindow>(m_ptrWindow));
	}

	//////Load Scenes//////

	m_scenes.clear();
	m_res = ResourceManager();
	std::string sFile = "Source\\Resources\\scenes\\test.xml";
	SceneLoader sceneLoader(sFile, &m_res, &m_scenes);

	if (m_scenes.empty()) {
		std::cout << "No scenes loaded\n";
		system("pause");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//////Initialize loaded scenes//////
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		(*it).second->initScene();
		(*it).second->setMessages(m_ptrLocalMessages);	//Allow scene to create messages for components
	}
}

void SceneComponent::handleMessage(std::shared_ptr<Message> msg)
{
	if (msg->sID == "Scene_Reload") {
		init();
	}
}

void SceneComponent::update(float dt)
{
	//Handle Inputs for active scene
	handleInput();

	//Create draw message for render component
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		(*it).second->update(dt);
		m_ptrLocalMessages->push_back(std::make_shared<RenderComponent::Draw>((*it).second));
	}
}
