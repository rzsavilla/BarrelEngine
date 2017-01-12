#pragma once
#include "stdafx.h"
#include "ResourceManager.h"
/* Abstract Scene class*/
class Scene
{
public:
	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void initScene(ResourceManager* res, int screenWidth,int screenHeight) = 0;

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