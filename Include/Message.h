#pragma once

#include <string>

/*! 
	Message stores an ID which indicates its purpose
	and the data that it stores.

	It is used to pass data/commands/instructions to or between components
*/


//Abstract struct
struct Message {
	std::string sID;
};

struct SetPositionMessage : public Message {
	SetPositionMessage(glm::vec3 newPos)
		:vPos(newPos)
	{
		sID = "SetPosition";
	}
	glm::vec3 vPos;	//New Position data
};

struct KeyEvent : public Message {
	KeyEvent(unsigned int key, bool isPressed)
		: iKey(key)
		, isDown(isPressed)
	{
		sID = "KeyEvent";
	}

	unsigned int iKey;
	bool isDown;
};