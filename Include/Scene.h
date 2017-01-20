#pragma once
#include "stdafx.h"
#include "ResourceManager.h"
#include "Drawable.h"
#include "Message.h"

#include "Model.h"
#include "Light.h"
#include "Text.h"

/* Abstract Scene class*/
class Scene: public Drawable
{
protected:
	unsigned int m_uiCameraActive;	//!< index of camera being used

	int m_iKey_W, m_iKey_S, m_iKey_A, m_iKey_D;
	int m_iKey_Escape;
	int m_iKey_Space;
	int m_iKey_Q;
	int m_iKey_E;
	int m_iKey_R;

	double m_dMouseX, m_dMouseY;
	double m_dPrevMouseX, m_dPrevMouseY;

	std::vector<std::shared_ptr<Message>>* m_ptrMessages;
	std::map<GLchar, Character>* m_ptrCharacters;			//Pointer to character used for create Text
	ResourceManager* m_ptrResources;						//Points to resource manager
public:
	~Scene() {};
	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void initScene() = 0;

	/*! Process GLFW inputs for scene
	*/
	virtual void handleInput(GLFWwindow* window) = 0;

	/** Update scene
	*/
	virtual void update(float dt) = 0;

	/** Draw scene.
	*/
	virtual void draw() = 0;

	/*! Allow seen to create messages
	*/
	void setMessages(std::vector<std::shared_ptr<Message>>* messages) {
		m_ptrMessages = messages;
	}

	/*!	Allows scene to create Text by passing pointer to characters texture
	*/
	void setCharacters(std::map<GLchar, Character>* characters);

	//Pointer to resources/gives scene access to resources
	void setResources(ResourceManager* res);
};