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
	std::vector<int>::iterator iter;
	iter = std::find(participators.begin(), participators.end(), idSender);
	if (iter == participators.end())
		participators.push_back(idSender);
	return 0;
}

int Session::getSessionId() const
{
	return sessionId;
}

QTime Session::getLastTime() const
{
	return messages.back().getDate();
}

void Session::setSessionId(int id)
{
	sessionId = id;
}

std::vector<int> Session::getParticipators() const
{
	return participators;
}

void Session::addParticipators(int userId)
{
	participators.push_back(userId);
}
