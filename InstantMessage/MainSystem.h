#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H
#include "User.h"
#include "Message.h"
#include "Session.h"
#include <vector>

class MainSystem
{
public:
	MainSystem();

private:
	static MainSystem *instance;
	User *systemUser;
	std::vector<User> friends;     //登陆用户的好友列表
	std::vector<Session> sessions;  //登陆用户的会话列表
	int *sessionList;

};

#endif // MAINSYSTEM_H
