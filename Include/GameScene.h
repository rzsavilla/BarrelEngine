#pragma once

#include <Scene.h>

#include "Model.h"
#include "Light.h"
#include "QuatCamera.h"

class GameScene :public Scene {
private:
	std::vector<Model> m_vModels;			//Store Models
	std::vector<Light> m_vLights;			//Store Lights
	std::vector<QuatCamera> m_vCamera;		//Store Cameras
	std::vector<GLSLProgram> m_vShaders;	//Store Shaders
public:
	GameScene();		//!< Default Constructor

	void initScene();

	void update();

	void render();

	void resize(int, int);
};