#include "Message.h"

Message::Message()
{

}

Message::Message(int idSender, QTime date, QString type, QString content)
{
	this->idSender = idSender;
	this->date = date;
	this->type = type;
	this->content = content;
}

int Message::getIdSender() const
{
	return idSender;
}

QTime Message::getDate() const
{
	return date;
}

QString Message::getType() const
{
	return type;
}

QString Message::getContent() const
{
	return content;
}
