#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H
#include "User.h"
#include "Message.h"


class MainSystem
{
public:
	MainSystem();

private:
	static MainSystem *instance;
	User *systemUser;
	int *userFriends;
	int *sessionList;

};

#endif // MAINSYSTEM_H
