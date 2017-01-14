#include <stdafx.h>
#include "GameScene.h"

void GameScene::updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera cam)
{
	//Pass camera uniforms to shader
	shader->setUniform("mView", cam.view());				//View matrix
	shader->setUniform("mProjection", cam.projection());	//Projection matrix
	shader->setUniform("viewPos", cam.position());			//Camera position
}

void GameScene::updateLight(std::shared_ptr<GLSLProgram> shader, Light light)
{
	shader->setUniform("lightPosition", light.getPosition());
	shader->setUniform("lightRadius", light.getRadius());

	//Pass light intesity
	shader->setUniform("La", light.getAmbient());	//Ambient light
	shader->setUniform("Ld", light.getDiffuse());	//Diffuse light
	shader->setUniform("Ls", light.getSpecular());	//Specular light
}

GameScene::GameScene()
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

void GameScene::initScene()
{

}

void GameScene::update(float dt)
{
	m_vModels.at(0).second.rotate(0.1f, Axis::yAxis);
	m_vModels.at(0).second.rotate(0.1f,Axis::zAxis);
	m_vCamera.at(m_iActiveCamera).second.rotate(0.001f, 0.0f);
}

void GameScene::render(GLFWwindow* window)
{
	//////////////////RENDER//////////
	for (auto modelIt = m_vModels.begin(); modelIt != m_vModels.end(); ++modelIt) {
		(*modelIt).second.getShader()->use();
		//Pass camera uniforms to shader (For active camera)
		updateCamera((*modelIt).second.getShader(), m_vCamera.at(m_iActiveCamera).second);
		//Pass light uniforms to shaders
		for (auto lightIt = m_vLights.begin(); lightIt != m_vLights.end(); ++lightIt) {
			updateLight((*modelIt).second.getShader(), (*lightIt).second);
		}
		//Draw model
		(*modelIt).second.draw();
	}

	for (auto robotIt = m_vRobots.begin(); robotIt != m_vRobots.end(); ++robotIt) {
		(*robotIt).second.getShader()->use();
		//Pass camera uniforms to shader (For active camera)
		updateCamera((*robotIt).second.getShader(), m_vCamera.at(m_iActiveCamera).second);
		//Pass light uniforms to shaders
		for (auto lightIt = m_vLights.begin(); lightIt != m_vLights.end(); ++lightIt) {
			updateLight((*robotIt).second.getShader(), (*lightIt).second);
		}
		//Draw model
		(*robotIt).second.draw();
	}
}

void GameScene::resize(int, int)
{
	
}