#include <stdafx.h>
#include "GameScene.h"
#include "SceneLoader.h"

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

void GameScene::nextCamera()
{
	if (m_uiCameraActive < m_vCamera.size()-1) m_uiCameraActive += 1;
}

void GameScene::prevCamera()
{
	if (m_uiCameraActive > 0) m_uiCameraActive -= 1;
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
	m_iKey_W = 0, m_iKey_S = 0, m_iKey_A = 0, m_iKey_D = 0;
	m_dMouseX = 0.0, m_dMouseY = 0.0;
	m_dPrevMouseX = 0.0, m_dPrevMouseY = 0.0;
	m_uiCameraActive = 0;
}

void GameScene::handleInput(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Key Press
	m_iKey_W = glfwGetKey(window, GLFW_KEY_W);
	m_iKey_S = glfwGetKey(window, GLFW_KEY_S);
	m_iKey_A = glfwGetKey(window, GLFW_KEY_A);
	m_iKey_D = glfwGetKey(window, GLFW_KEY_D);

	m_iKey_Escape = glfwGetKey(window, GLFW_KEY_ESCAPE);
	m_iKey_Space = glfwGetKey(window, GLFW_KEY_ESCAPE);
	m_iKey_Q = glfwGetKey(window, GLFW_KEY_Q);
	m_iKey_E = glfwGetKey(window, GLFW_KEY_E);

	//Mouse movement
	glfwGetCursorPos(window, &m_dMouseX, &m_dMouseY);
	m_dDeltaMouseX = m_dPrevMouseX - m_dMouseX;
	m_dDeltaMouseY = m_dPrevMouseY - m_dMouseY;
	m_dPrevMouseX = m_dMouseX;
	m_dPrevMouseY = m_dMouseY;
}

void GameScene::update(float dt)
{
	float rotateVel = 10.0f * dt;
	m_vModels.at(0).second.rotate(0.1f, Axis::yAxis);
	m_vModels.at(0).second.rotate(0.1f,Axis::zAxis);

	//Robot movement
	if (m_iKey_W) m_vRobots.begin()->second.moveForward();
	else if (m_iKey_S) m_vRobots.begin()->second.moveBackward();
	if (m_iKey_A) m_vRobots.begin()->second.turnLeft();
	else if (m_iKey_D) m_vRobots.begin()->second.turnRight();

	//Switch Camera
	if (m_iKey_Q) prevCamera();
	else if (m_iKey_E) nextCamera();
	m_iKey_Q = false;
	m_iKey_E = false;

	//Reload Scene
	if (m_iKey_Escape) m_ptrMessages->push_back(std::make_shared<SceneMessage::Reload>());

	//Close Game
	//if (m_iKey_Escape) m_ptrMessages->push_back(std::make_shared<SceneMessage::Exit>());

	//Rotate camera based on mouse movement
	if (!m_vCamera.empty()) {
		m_vCamera.at(m_uiCameraActive).second.rotate((-m_dDeltaMouseX * rotateVel) * (1 / 60.0f), (-m_dDeltaMouseY * rotateVel) * (1 / 60.0f));
	}
	//Update Robot
	for (auto robotIt = m_vRobots.begin(); robotIt != m_vRobots.end(); ++robotIt) {
		(*robotIt).second.update(dt);
	}
}

void GameScene::draw()
{
	gl::Enable(gl::DEPTH_TEST);
	//////////////////RENDER//////////
	for (auto modelIt = m_vModels.begin(); modelIt != m_vModels.end(); ++modelIt) {
		(*modelIt).second.getShader()->use();
		//Pass camera uniforms to shader (For active camera)
		updateCamera((*modelIt).second.getShader(), m_vCamera.at(m_uiCameraActive).second);
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
		updateCamera((*robotIt).second.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//Pass light uniforms to shaders
		for (auto lightIt = m_vLights.begin(); lightIt != m_vLights.end(); ++lightIt) {
			updateLight((*robotIt).second.getShader(), (*lightIt).second);
		}
		//Draw model
		(*robotIt).second.draw();
	}
	gl::Disable(gl::DEPTH_TEST);
}

void GameScene::resize(int, int)
{
	
}