#pragma once

/*
	//Singleton using smartpointer implementation guide
	http://silviuardelean.ro/2012/06/05/few-singleton-approaches/
*/

#include <stdafx.h>
#include <memory>
#include <mutex>


class Engine {
private:
	int i;

	//////Singleton///////
	Engine();		//!< Private Constructor

	static bool m_bInstance;				//!< Instance flag
	static std::shared_ptr<Engine>& m_ptrInstance;			//!< Pointer to instance
	
public:
	//////Singleton///////
	~Engine();		//!< Destructor

	static std::shared_ptr<Engine>& getInstance();		//!< Returns pointer to engine instance

	void update(float dt);
};