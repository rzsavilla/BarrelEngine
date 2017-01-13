#include <stdafx.h>
#include "GameScene.h"

void GameScene::updateLight(std::shared_ptr<GLSLProgram> shader, Light light)
{
	shader->setUniform("lightPosition", light.getPosition());
	shader->setUniform("lightRadius", light.getPosition());

	shader->setUniform("La", light.getAmbient());	//Ambient light
	shader->setUniform("Ld", light.getDiffuse());	//Diffuse light
	shader->setUniform("Ls", light.getSpecular());	//Specular light
}

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

void GameScene::render(GLFWwindow* window)
{
	////////////////RENDER//////////
	gl::Enable(gl::DEPTH_BUFFER_BIT);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);


	for (auto modelIt = m_vModels.begin(); modelIt != m_vModels.end(); ++modelIt) {
		for (auto lightIt = m_vLights.begin(); lightIt != m_vLights.end(); ++lightIt) {
			//Pass lights to shaders
			//Light
			updateLight((*modelIt).second.getShader(), (*lightIt).second);
		}
	}


	//Update lights 
	//for (auto modelIt = m_vModels.begin(); modelIt != m_vModels.end(); ++modelIt) {
	//	for (auto lightIt = m_vLights.begin(); lightIt != m_vLights.end(); ++modelIt) {
	//		//Pass lights to shaders
	//		//Light
	//		/*(*modelIt).second.getShader()->setUniform("lightPosition", (*lightIt).second.getPosition());
	//		(*modelIt).second.getShader()->setUniform("lightRadius", (*lightIt).second.getRadius());*/
	//	}
	//}
	////Light intensity
	//prog.setUniform("La", (*lightIt).second.getAmbient());	//Ambient light
	//prog.setUniform("Ld", (*lightIt).second.getDiffuse());	//Diffuse light
	//prog.setUniform("Ls", (*lightIt).second.getSpecular());	//Specular light


	//(*modelIt).second.getShader();

	//}

	//

	GLSLProgram p;
	for (auto it = m_vModels.begin(); it != m_vModels.end(); ++it) {
		(*it).second.draw(&p);
	}

	//glfwSwapInterval(1);		//VSYNC OFF
	glfwSwapBuffers(window);
	gl::Disable(gl::DEPTH_BUFFER_BIT);
}

void GameScene::resize(int, int)
{
	
}

void updateLight(GLSLProgram& prog, Light light, Material material, QuatCamera cam);