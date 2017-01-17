#pragma once

#include "Scene.h"

class StartScene : public Scene {
private:

public:
	void initScene();
	void handleInput(GLFWwindow* window);
	void update(float dt);

	void draw();
};