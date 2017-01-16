#pragma once

#include <Scene.h>

#include "Model.h"
#include "Light.h"
#include "QuatCamera.h"
#include "MyRobot.h"
#include "Component.h"

class GameScene :public Scene {
private:
	std::vector<std::pair<std::string, Model>> m_vModels;			//Store Models
	std::vector<std::pair<std::string, Light>> m_vLights;			//Store Lights
	std::vector<std::pair<std::string, QuatCamera>> m_vCamera;		//Store Cameras
	std::vector<std::pair<std::string, MyRobot>> m_vRobots;			//Store Cameras
	std::vector<std::pair<std::string, std::shared_ptr<GLSLProgram>>>	m_vShaders;	//Store pointers to shader programs

	void updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera cam);
	void updateLight(std::shared_ptr<GLSLProgram> shader, Light light);

	double m_dDeltaMouseX;	//!< Mouse position difference X
	double m_dDeltaMouseY;	//!< Mouse position difference Y

	void nextCamera();		//!< Switch active camera
	void prevCamera();		//!< Switch active camera
public:
	GameScene();		//!< Default Constructor

	void addModel(std::pair<std::string, Model> model);
	void addLight(std::pair<std::string, Light> light);
	void addCamera(std::pair<std::string, QuatCamera> camera);
	void addRobot(std::pair<std::string, MyRobot> robot);

	void initScene();

	void handleInput(GLFWwindow* window);

	void update(float dt);

	void draw();

	void resize(int, int);
};