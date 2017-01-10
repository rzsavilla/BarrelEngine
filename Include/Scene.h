#pragma once
#include "stdafx.h"
/* Abstract Scene class*/
class Scene
{
public:
	Scene();	//!< Default constructor

	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void initScene() = 0;

	/**
	This is called prior to every frame.  Use this
	to update your animation.
	*/
	virtual void update(float dt) = 0;

	/**
	Draw your scene.
	*/
	virtual void render() = 0;

	/**
	Called when screen is resized
	*/
	virtual void resize(int, int) = 0;

protected:
	bool m_animate;
};