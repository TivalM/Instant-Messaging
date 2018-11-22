#ifndef USER_H
#define USER_H
#pragma once
#include <QString>

class User
{
public:
	explicit User();
	int getIdUser() const;
	QString getNameUser() const;
	QString getAccountUser() const;
	int getState() const;

private:
	int idUser;
	QString nameUser;
	QString accountUser;
	int state;
};


#endif // USER_H
