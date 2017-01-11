/*!
	\class Component
	Abstract class
	A base/Super/parent class for GameObject Components
*/

//http://www.randygaul.net/tag/c/

#pragma once

#include <stdafx.h>
#include <Message.h>

class Component {
protected: 
	std::string m_sComponentID;
	/*!
		Pointer to vector of message pointers	
		//Allows pointer to pass messages to object for other components to read
	*/
	std::vector<Message*>* m_ptrLocalMessages;
	void sendMessage(Message* msg);		//!< Creates local message for components in GameObject to read
public:
	virtual void init() = 0;							//!< Initialize component
	
	virtual void handleMessage(Message* msg) = 0;		//!< Each component will read and ignore Messages depending on implementation of this function

	virtual void update(float dt) = 0;					//!< Updates component during game loop

	/*!
		Allows component to access all local messages
	*/
	void setLocalMsgPtr(std::vector<Message*>* ptr);

	/*!
		Returns ComponentID/ Component Type eg Transformable Movable etc in string
	*/
	std::string getComponentID() { return m_sComponentID; }

	virtual ~Component() {};		//!< Destructor
};