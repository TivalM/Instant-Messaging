#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H
#include "User.h"
#include "Message.h"
#include "Session.h"
#include "ClientCore.h"
#include <vector>
#include <QtCore>

#define PREURL "127.0.0.0:8081"

class MainSystem
{
public:
	MainSystem();
	MainSystem *getSystem();
	//系统登录时从服务器读入信息，此处get的是系统中已保存的信息
	//Id是服务器为用户分配的唯一标识符，账号是用户手动输入用于登陆的唯一的身份信息
	int signUp(QString account, QString password, QString nickname);
	int login(QString account, QString password);
	int loadUserInfo(); //load指从服务器载入
	int loadFriendList();
	int loadSessions();
	int ifSessionExist(int sessionId);
	int loadMessages(int sessionId);
	QPixmap *loadImg(int id);
	int getFriendInfoById(int id);
	Session &getSessoinById(unsigned int id);
	int getUserInfo(QString account);
	int queryUser(QString account);
	int sendFriendRequest(QString account);
	int deleteFriend(QString account);
	int modifyUserInfo(QString nickname, QString area);
	static MainSystem *getMainSystem();

private:
	static MainSystem *mainSystem;
	User *systemUser;
	std::vector<User> friends;     //登陆用户的好友列表
	std::vector<Session> sessions;  //登陆用户的会话列表
	ClientCore *clientCore;
};

#endif // MAINSYSTEM_H
