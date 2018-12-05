#ifndef MESSAGE_H
#define MESSAGE_H
#pragma once
#include <QTime>
#include <QString>
class Message
{
public:
	Message();
	//类型待修改
	Message(int idSender, QTime date, QString type, QString content);
	int getIdSender() const;
	QTime getDate() const;
	QString getType() const;
	QString getContent() const;
	int getBelongsToSession() const;

private:
	int idSender;
	QTime date;
	QString type;
	QString content;
};

#endif // MESSAGE_H
