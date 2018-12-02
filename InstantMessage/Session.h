#ifndef SESSION_H
#define SESSION_H
#pragma once
#include <vector>
#include "Message.h"

class Session
{
public:
	Session();
	Session(int id);
	std::vector<Message> getMessages() const;
	int insertMessage(int idSender, QString date, QString type, QString content);
	int getSessionId() const;

	void setSessionId(int value);

private:
	int sessionId;
	std::vector<Message> messages;
};

#endif // SESSION_H
