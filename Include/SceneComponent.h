#pragma once

#include "Component.h"
#include "Text.h"

class SceneComponent: public Component {
private:
	GLFWwindow *m_ptrWindow;
	ResourceManager m_res;
	std::vector<std::pair<std::string, std::shared_ptr<Scene>>> m_scenes;
	std::map<GLchar, Character> Characters;

	unsigned int m_uiActiveScene;

	bool m_bWindowLoaded = false;
	bool m_bReload = false;		//Flag for reloading the scene/ *fix ensures render component is empty

	/*! Process GLFW inputs for active scene
	*/
	void handleInput();

	std::shared_ptr<Text> m_FPSText;

	std::shared_ptr<Text> getTextObject(std::string id);
	std::vector<std::pair<std::string,std::shared_ptr<Text>>> m_vTexts;
public:
	void init();
	void handleMessage(std::shared_ptr<Message> msg);
	void update(float dt);
};