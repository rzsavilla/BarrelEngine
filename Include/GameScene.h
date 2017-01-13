#pragma once

#include <Scene.h>

#include "Model.h"
#include "Light.h"
#include "QuatCamera.h"
#include "MyRobot.h"

class GameScene :public Scene {
private:
	std::vector<std::pair<std::string, Model>> m_vModels;			//Store Models
	std::vector<std::pair<std::string, Light>> m_vLights;			//Store Lights
	std::vector<std::pair<std::string, QuatCamera>> m_vCamera;		//Store Cameras
	std::vector<std::pair<std::string, MyRobot>> m_vRobots;		//Store Cameras
public:
	GameScene();		//!< Default Constructor

	void initScene();

	void update(float dt);

	void addModel(std::pair<std::string, Model> model);
	void addLight(std::pair<std::string, Light> light);
	void addCamera(std::pair<std::string, QuatCamera> camera);
	void addRobot(std::pair<std::string, MyRobot> robot);

	void render();

	void resize(int, int);
};