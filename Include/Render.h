#pragma once

#include <stdafx.h>
#include "Component.h"
#include "Drawable.h"
#include "Light.h"

namespace RenderComponent {

	struct Draw : public Message {
		Draw(std::shared_ptr<Drawable> obj)
			:drawObj(obj)
		{
			sID = "Render_Draw";
		}

		std::shared_ptr<Drawable> drawObj;		//Object to be drawn
		//std::shared_ptr<GLSLProgram> ptrShader;	//Shader used to draw
	};

	struct SetCamera : public Message {
		SetCamera(QuatCamera* cam)
			:camera(cam)
		{
			sID = "Render_SetCamera";
		}
		QuatCamera* camera;		//For Camera View and projection matrices
	};

	struct SetLights : public Message {
		SetLights(std::vector<std::pair<std::string, Light>>* lights)
			: vLights(lights)
		{
			sID = "Render_SetLights";
		}
		std::vector<std::pair<std::string, Light>>* vLights;
	};
}

class Render: public Component {
private:
	GLFWwindow* m_ptrWindow;

	//std::vector<std::pair<std::shared_ptr<GLSLProgram>, std::shared_ptr<Drawable>>> m_ptrDrawObjects;	//Stores pointers for objects that need to be drawn along with shader to be used
	std::vector<std::shared_ptr<Drawable>> m_ptrDrawObjects;	//Stores pointers for objects that need to be drawn along with shader to be used
	QuatCamera* m_ptrCamera;					//Pointer to camera in use
	std::vector<std::pair<std::string, Light>>* m_ptrLights;			//Pointer to vector of lights

	void updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera* cam);
	void updateLight(std::shared_ptr<GLSLProgram> shader, Light light);

public:
	Render();

	//Set pointer for window to draw onto
	void setWindow(GLFWwindow* ptr);

	void init();
	void handleMessage(std::shared_ptr<Message> msg);
	void update(float dt);
};
