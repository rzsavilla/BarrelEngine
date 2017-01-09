/*!
	\class Component
	Abstract class
*/

//http://www.randygaul.net/tag/c/

#pragma once

#include <stdafx.h>

class Component;

struct Message {
	Message(const Component& obj, const std::string& msg)
		: m_obj(&obj)
		, m_msg(msg)
	{}
	const Component* m_obj;
	std::string m_msg;
};

class Component {

public:
	virtual void init(void) = 0;						//!< Initialize component
	
	virtual void update(float dt) = 0;					//!< Updates component during game loop

	virtual void sendMessage(const Message& msg) = 0;

	virtual ~Component() {};		//!< Destructor
};