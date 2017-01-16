#pragma once
#include "stdafx.h"
#include "ResourceManager.h"
#include "Drawable.h"
#include "Message.h"

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

	double m_dMouseX, m_dMouseY;
	double m_dPrevMouseX, m_dPrevMouseY;

	std::vector<std::shared_ptr<Message>>* m_ptrMessages;
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

	/** Called when screen is resized
	*/
	virtual void resize(int, int) = 0;

	/*! Allow seen to create messages
	*/
	void setMessages(std::vector<std::shared_ptr<Message>>* messages) {
		m_ptrMessages = messages;
	}
};