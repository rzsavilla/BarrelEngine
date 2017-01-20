#pragma once

#include "Scene.h"
#include "MyTimer.h"
#include "Text.h"

class SplashScene : public Scene {
private:
	MyTimer timer;
	std::shared_ptr<Text> m_LoadingText;
public:
	SplashScene();
	void initScene();
	void handleInput(GLFWwindow* window);
	void update(float dt);

	void draw();
};