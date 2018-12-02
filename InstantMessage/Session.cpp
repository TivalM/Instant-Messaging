#include "Session.h"

Session::Session()
{
	messages.reserve(16);
}

Session::Session(int id)
{
	this->sessionId = id;
	messages.reserve(16);
}

std::vector<Message> Session::getMessages() const
{
	return messages;
}

int Session::insertMessage(int idSender, QString date, QString type, QString content)
{
	Message newMessage(idSender, QTime::fromString(date), type, content);
	messages.push_back(newMessage);
	return 0;
}

int Session::getSessionId() const
{
	return sessionId;
}

void Session::setSessionId(int id)
{
	sessionId = id;
}
