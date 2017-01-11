#include <stdafx.h>
#include "Component.h"

void Component::sendMessage(Message * msg)
{
	m_ptrLocalMessages->push_back(msg);
}

void Component::setLocalMsgPtr(std::vector<Message*>* ptr)
{
	m_ptrLocalMessages = ptr;
}
