#include "User.h"

User::User()
{

}

int User::getIdUser() const
{
	return idUser;
}

QString User::getNameUser() const
{
	return nameUser;
}

QString User::getAccountUser() const
{
	return accountUser;
}

int User::getState() const
{
	return state;
}
