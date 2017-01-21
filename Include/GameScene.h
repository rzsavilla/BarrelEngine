/**
* @class   GameScene
* @brief  Game Scene updates, runs and draws game loop
* Game Scenes stores game objects and updates game loop.
* Scene contains and updates game logic.
*/

#pragma once

#include <Scene.h>

#include "Model.h"
#include "Light.h"
#include "QuatCamera.h"
#include "MyRobot.h"
#include "Component.h"
#include "MyTimer.h"
#include "Text.h"

class GameScene :public Scene {
private:
	std::vector<std::pair<std::string, Model>> m_vModels;		//!< Store Models with id
	std::vector<std::pair<std::string, Light>> m_vLights;		//!< Store Lights with id
	std::vector<std::pair<std::string, QuatCamera>> m_vCamera;	//!< Store Cameras with id
	std::vector<std::pair<std::string, MyRobot>> m_vRobots;		//!< Store Robots with id
	std::vector<std::pair<std::string, std::shared_ptr<GLSLProgram>>>	m_vShaders;		//Store pointers to shader programs with id

	void updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera cam);		//!< Passes camera uniforms for shader program
	void updateLights(std::shared_ptr<GLSLProgram> shader);						//!< Passes light uniforms  for shader program

	double m_dDeltaMouseX;	//!< Mouse position difference X
	double m_dDeltaMouseY;	//!< Mouse position difference Y

	void nextCamera();		//!< Switch active camera to next camera
	void prevCamera();		//!< Switch active camera to previous camera

	MyTimer m_camSwitchDelay;	//!< Delay timer for switching cameras

	//! Calculates distance between robot and model to determine if a collision has occured
	bool collision(MyRobot* robot, Model* model);

	std::shared_ptr<Text> m_PickupCounterText;	//!< Text object for
	int m_iTotalPickups;		//!< Total number of pickups when scene is initialized
	int m_iCollected;			//!< Tracks the number of pickups collected in the scene
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