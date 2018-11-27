#ifndef SESSION_H
#define SESSION_H
#pragma once
#include <vector>
#include "Message.h"

class Session
{
public:
	Session();

private:
	std::vector<Message> messages;
};

#endif // SESSION_H
