#pragma once

/*
	//Singleton using smartpointer implementation guide
	http://silviuardelean.ro/2012/06/05/few-singleton-approaches/

	//Component based engine design
	http://www.randygaul.net/2013/05/20/component-based-engine-design/
*/

#include <stdafx.h>
#include <memory>
#include <mutex>


class Engine {
private:
	//////Singleton///////
	Engine();		//!< Private Constructor

	static bool m_bInstance;								//!< Instance flag
	static std::shared_ptr<Engine>& m_ptrInstance;			//!< Pointer to instance

	//////Game Loop functions////////
	void gameLoop();			//!< Run the game loop
	void render();
public:
	//////Singleton///////
	~Engine();		//!< Destructor

	static std::shared_ptr<Engine>& getInstance();		//!< Returns pointer to engine instance

	void update(float dt);
};