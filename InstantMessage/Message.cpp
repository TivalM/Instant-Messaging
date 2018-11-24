#include "Message.h"

Message::Message()
{

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

int Message::getBelongsToSession() const
{
	return belongsToSession;
}
