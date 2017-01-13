#include <stdafx.h>
#include "GameScene.h"

GameScene::GameScene()
{

}

void GameScene::initScene()
{

}

void GameScene::update(float dt)
{

}

void GameScene::addModel(std::pair<std::string, Model> model)
{
	m_vModels.push_back(model);
}

void GameScene::addLight(std::pair<std::string, Light> light)
{
	m_vLights.push_back(light);
}

void GameScene::addCamera(std::pair<std::string, QuatCamera> camera)
{
	m_vCamera.push_back(camera);
}

void GameScene::addRobot(std::pair<std::string, MyRobot> robot)
{
	m_vRobots.push_back(robot);
}

void GameScene::render()
{
	GLSLProgram p;
	for (auto it = m_vModels.begin(); it != m_vModels.end(); ++it) {
		(*it).second.draw(&p);
	}
}

void GameScene::resize(int, int)
{

}
