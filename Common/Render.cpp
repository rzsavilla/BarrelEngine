#include <stdafx.h>
#include "..\Include\Render.h"

void Render::updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera* cam)
{
	//Pass camera uniforms to shader
	shader->setUniform("mView", cam->view());				//View matrix
	shader->setUniform("mProjection", cam->projection());	//Projection matrix
	shader->setUniform("viewPos", cam->position());			//Camera position
}

void Render::updateLight(std::shared_ptr<GLSLProgram> shader, Light light)
{
	shader->setUniform("lightPosition", light.getPosition());
	shader->setUniform("lightRadius", light.getRadius());

	//Pass light intesity
	shader->setUniform("La", light.getAmbient());	//Ambient light
	shader->setUniform("Ld", light.getDiffuse());	//Diffuse light
	shader->setUniform("Ls", light.getSpecular());	//Specular light
}

Render::Render()
{
}

void Render::setWindow(GLFWwindow * ptr)
{
	m_ptrWindow = ptr;
}

void Render::init()
{

}

void Render::handleMessage(std::shared_ptr<Message> msg)
{
	if (msg->sID == "Render_Draw") {
		//Get data from message
		std::shared_ptr<Drawable> drawable = static_cast<RenderComponent::Draw*>(msg.get())->drawObj;
		//std::shared_ptr<GLSLProgram> shader = static_cast<RenderComponent::Draw*>(msg)->ptrShader;

		//Store data
		m_ptrDrawObjects.push_back(drawable);
		//m_ptrDrawObjects.push_back(std::pair<std::shared_ptr<GLSLProgram>, Drawable*>(shader,draw));	
	}
	else if (msg->sID == "Render_SetCamera") {
		//Get data from message
		QuatCamera* cam = static_cast<RenderComponent::SetCamera*>(msg.get())->camera;
		m_ptrCamera = cam;					//Store pointer for camera object
	}
	else if (msg->sID == "Render_SetLights") {
		//Get data from message
		std::vector<std::pair<std::string, Light>>* vLights = static_cast<RenderComponent::SetLights*>(msg.get())->vLights;
		m_ptrLights = vLights;					//Store pointer for vector of lights
	}
	else if (msg->sID == "SetWindow") {
		//Get data from message
		m_ptrWindow = static_cast<SetWindow*>(msg.get())->window;
	}
	else {

	}

}

void Render::update(float dt)
{
	gl::Enable(gl::DEPTH_TEST);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	for (auto objIt = m_ptrDrawObjects.begin(); objIt != m_ptrDrawObjects.end(); ++objIt) {
		(*objIt)->draw();
	}
	m_ptrDrawObjects.clear();
	gl::Disable(gl::DEPTH_TEST);

	glfwSwapInterval(1);		//VSYNC OFF
	if (m_ptrWindow) {
		glfwSwapBuffers(m_ptrWindow);
	}
}
