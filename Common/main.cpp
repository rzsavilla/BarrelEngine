#include <stdafx.h>

#include "Engine.h"
#include "SceneComponent.h"

int main() {
	Engine engine;
	engine.attachComponent(std::make_unique<Render>());
	engine.attachComponent(std::make_unique<SceneComponent>());
	engine.init();
	engine.run();

	return 0;
}