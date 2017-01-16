#pragma once

#include "Component.h"

class SceneComponent: public Component {
private:
	GLFWwindow *m_ptrWindow;
	ResourceManager m_res;
	std::vector<std::pair<std::string, std::shared_ptr<Scene>>> m_scenes;

	unsigned int m_uiActiveScene;

	bool m_bWindowLoaded = false;

	/*! Process GLFW inputs for active scene
	*/
	void handleInput();
public:
	void init();
	void handleMessage(std::shared_ptr<Message> msg);
	void update(float dt);
};