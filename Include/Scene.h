#pragma once
#include "stdafx.h"
#include "ResourceManager.h"
/* Abstract Scene class*/
class Scene
{
public:
	~Scene() {};
	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void initScene() = 0;

	/** Update scene
	*/
	virtual void update(float dt) = 0;

	/** Draw scene.
	*/
	virtual void render() = 0;

	/** Called when screen is resized
	*/
	virtual void resize(int, int) = 0;
};