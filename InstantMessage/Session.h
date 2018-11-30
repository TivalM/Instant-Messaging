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
	int insertMessage(int idSender, QTime date, QString type, QByteArray content);
	int getSessionId() const;

private:
	int sessionId;
	std::vector<Message> messages;
};

#endif // SESSION_H
