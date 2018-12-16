#include "MainSystem.h"

MainSystem *MainSystem::mainSystem = nullptr;


MainSystem::MainSystem(QObject *parent) : QObject(parent)
{
	clientCore = new ClientCore();
	//预留空间
	//  friends.reserve(16);
	//  sessions.reserve(8);
	//测试
//	friends.push_back(User(0, "Core", "55789", QString::fromLocal8Bit("广州"), new QPixmap(":/src/image/head2.png")));
//	friends.push_back(User(1, "Karl", "46498", QString::fromLocal8Bit("深圳"), new QPixmap(":/src/image/head3.png")));
//	friends.push_back(User(2, "Macy", "78416", QString::fromLocal8Bit("贵阳"), new QPixmap(":/src/image/head4.png")));
//	friends.push_back(User(3, "Tanya", "12389", QString::fromLocal8Bit("成都"), new QPixmap(":/src/image/head5.png")));
//	friends.push_back(User(4, "Terry", "77866", QString::fromLocal8Bit("广西"), new QPixmap(":/src/image/head6.png")));
//	friends.push_back(User(5, "Able", "45589", QString::fromLocal8Bit("北京"), new QPixmap(":/src/image/head7.png")));
//	friends.push_back(User(6, "Jocelyn", "95678", QString::fromLocal8Bit("重庆"), new QPixmap(":/src/image/head8.png")));

//	sessions.push_back(Session(0));
//	sessions.at(0).addParticipators(2);
//	sessions.push_back(Session(1));
//	sessions.at(1).addParticipators(1);
//	sessions.push_back(Session(2));
//	sessions.at(2).addParticipators(6);
//	sessions.push_back(Session(3));
//	sessions.at(3).addParticipators(5);
}


std::vector<Session> MainSystem::getSessions()const
{
	return sessions;
}

std::vector<User> MainSystem::getFriends() const
{
	return friends;
}

MainSystem *MainSystem::getSystem()
{
	if (mainSystem == nullptr)
		mainSystem = new MainSystem();
	return mainSystem;
}

User *MainSystem::getFriendById(int id)
{
	int i = 0;
	for (auto iter : friends) {
		if (iter.getIdUser() == id)
			return &friends.at(i);
		i++;
	}
	return nullptr;
}

User *MainSystem::getFriendByAccount(QString account)
{
	int i = 0;
	for (auto iter : friends) {
		if (iter.getAccountUser() == account)
			return &friends.at(i);
		i++;
	}
	return nullptr;
}

User *MainSystem::getSystemUser()
{
	return systemUser;
}

Session &MainSystem::getSessoinById(unsigned int id)
{

	for (unsigned  int i = 0; i < sessions.size(); i++)
		if (sessions.at(i).getSessionId() == id)
			return sessions.at(i);
}

int MainSystem::signUp(QString account, QString password, QString nickname)
{
	QString u = QString("%1/user/register").arg(PREURL);
	QByteArray postData;
	postData.append(QString("account=%1&password=%2&name=%3").arg(account).arg(password).arg(nickname));
	QUrl url(u);
	QNetworkRequest request(url);
	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
	//提交请求并得到结果
	QNetworkReply *reply = clientCore->sendPostRequset(request, postData);

	if (reply == nullptr)
		return -2;  //获取回复失败(网络状况不明)
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());

	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		if (json["code"].toInt() == 1) {
			reply->deleteLater();
			return 0;       //注册成功
		} else {
			delete reply;
			return -3;      //账号已存在
		}
	} else {
		qDebug() << "Sign Up:  " << strReply;
		delete reply;
		return -1;  //无法解析Json
	}
}

int MainSystem::login(QString account, QString password)
{
	QString u = QString("%1/user/login").arg(PREURL);
	QByteArray postData;
	postData.append(QString("account=%1&password=%2").arg(account).arg(password));
	QUrl url(u);

	QNetworkRequest request(url);

	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
	QNetworkReply *reply = clientCore->sendPostRequset(request, postData);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());

	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		systemUser = new User(account);

		if (json["code"].toInt() == 1) {    //在服务器登陆成功
			//请求该系统用户的其它信息并初始化
			if (loadUserInfo() == 0 && loadFriendList() == 0) {
				clientCore->initWebSocket(QUrl(QString("ws://120.78.120.65:8080/webSocket/%2").arg(systemUser->getIdUser())));
				sortFriends();
				delete reply;
				return 0;
			} else {
				delete reply;
				return -5;//载入用户信息失败
			}
		} else {
			delete reply;
			qDebug() << "fail when login";
			return -4;//用户名或密码错误
		}
	} else {
		qDebug() << "Login:  " << strReply;
		return -1;  //无法解析Json
	}
}

int MainSystem::loadUserInfo()
{
	QUrl url(QString("%1/user/info").arg(PREURL));

	QNetworkRequest request;
	QVariant val;
	val.setValue(clientCore->getCookie());
	qDebug() << clientCore->getCookie();
	request.setUrl(url);
	request.setHeader(QNetworkRequest::CookieHeader, val);
	QNetworkReply *reply = clientCore->sendGetRequset(request);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());
	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		if (json["code"] == 1) {    //成功
			//读取该系统用户的其它信息，更新本地内存
			QJsonObject data = json["data"].toObject();
			QPixmap *img = loadImg(data["userId"].toInt());
			if (img == nullptr) {
				qDebug() << "can not load headImg " << data["userId"].toInt();
			}
			//更新用户其它信息
			systemUser->setInfo(data["userId"].toInt(), data["name"].toString(), data["area"].toString(), img);
			emit initSelfInfoWidgets();
			//得知登录的用户后初始化websocket连接
			reply->deleteLater();
			delete img;
			return 0;
		} else {
			qDebug() << "fail when loadUserInfo";
			return -5; //失败
		}
	} else {
		qDebug() << "LoadUserInfo:  " << strReply;
		return -1;  //无法解析Json
	}
}

int MainSystem::loadFriendList()
{
	QUrl url(QString("%1/user/friendList").arg(PREURL));
	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply *reply = clientCore->sendGetRequset(request);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	qDebug() << strReply;
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());
	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		if (json["code"] == 1) {    //成功
			//得到用户列表
			QJsonObject data = json["data"].toObject();
			QJsonArray list = data["list"].toArray();
			qDebug() << "Load Friend List:" << list;
			for (auto iter : list) {
				QJsonObject element = iter.toObject();
				QPixmap *img = loadImg(element["userId"].toInt());
				if (img == nullptr) {
					qDebug() << "can not load headimg " << element["userId"].toInt();
				}
				//account尚不存在
				friends.push_back(User(element["userId"].toInt(), element["name"].toString(),
				                       element["account"].toString(), element["area"].toString(), img));
			}
			emit(initFriendsWidgets());
			delete reply;
			return 0;
		} else {
			delete reply;
			qDebug() << "fail when loadFriendList";
			return -6; //失败
		}
	} else {
		qDebug() << "LoadFriendList:  " << strReply;
		return -1;
	}
}

int MainSystem::loadSessions()
{
	//待完成
	QUrl url(QString(""));
	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply *reply = clientCore->sendGetRequset(request);
	if (reply == nullptr)
		return -2;
	return 0;
}

int MainSystem::ifSessionExist(int sessionId)
{
	int i  = 0;
	for (auto iter : sessions) {
		if (iter.getSessionId() == sessionId)
			return i;
		i++;
	}
	return -1;
}

int MainSystem::loadMessages(int sessionId)
{
	QUrl url(QString("%1/message/historyMessage?chatSessionId=%2").arg(PREURL).arg(sessionId));
	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply *reply = clientCore->sendGetRequset(request);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());
	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		//得到Json
		if (json["code"] == 1) { //成功
			//找到对应的Session
			int index = ifSessionExist(sessionId);
			if (index != -1) {
				//找到session
				Session sessionNow = sessions.at(index);
				QJsonObject data = json["data"].toObject();
				//获取消息列表
				QJsonArray list = data["list"].toArray();
				for (auto iter : list) {
					//对于每一条消息字段
					QJsonObject element = iter.toObject();
					//类型待修改
					sessionNow.insertMessage(element["sender"].toInt(), element["time"].toString(),
					                         element["type"].toString(), element["msg"].toString());
				}
			} else {
				//需新建Session,此时需要的所有信息应当都在报文中
				Session newSession = Session(sessionId);
				QJsonObject data = json["data"].toObject();
				//获取消息列表
				QJsonArray list = data["list"].toArray();
				//更新参与者
				//
				for (auto iter : list) {
					//对于每一条消息字段
					QJsonObject element = iter.toObject();
					//类型待修改
					newSession.insertMessage(element["sender"].toInt(), element["time"].toString(),
					                         element["type"].toString(), element["msg"].toString());
				}
				sessions.push_back(newSession);
			}
			sortSessions();
			delete reply;
			return 0;
		} else {
			qDebug() << "fail when loadMessages " << sessionId;
			delete reply;
			return -6;   //失败
		}
	} else {
		qDebug() << "LoadMessage:  " << strReply;
		return -1;
	}
}

int MainSystem::loadAllMessages()
{
	for (auto iter : sessions)
		if (loadMessages(iter.getSessionId()) != 0)
			return -1;
	return 0;
}

QPixmap *MainSystem::loadImg(int id)
{
	QPixmap *img = new QPixmap();
	QUrl url(QString("%1/static/image/%2.jpg").arg(PREURL).arg(id));
	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply *reply = clientCore->sendGetRequset(request);
	qDebug() << "Load Img" << id;
	if (img->loadFromData(reply->readAll()))
		return img;
	delete img;
	return nullptr;
}

int MainSystem::createASession(int peerId)
{
	//发出一个请求，成功后得到系统返回的Session id
	//创建这个会话
	Session newSession = Session(sessions.size());
	newSession.addParticipators(peerId);
	sessions.push_back(newSession);
	return 0;
}

int MainSystem::sendfriendInvite(int peerId)
{
	//Websocket
	return 0;
}

int MainSystem::sendMessage(int sessoinId)
{
	//Websocket
	return 0;
}

int MainSystem::sortSessions()
{
	//按最后一条消息的时间排序
	//转为unsigned int可以解除警告
	int i, j;
	Session *temp;
	for (i = 1; i < sessions.size(); i++) {
		temp = &sessions.at(i);
		j = i - 1;
		while (j >= 0 && sessions.at(j).getLastTime() > temp->getLastTime()) {
			sessions.at(j + 1) = sessions.at(j);
			j--;
		}
		sessions.at(j + 1) = *temp;
	}
	return 0;
}

int MainSystem::sortFriends()
{
	if (friends.size() <= 1)
		return 0;
	int i, j;
	User *temp = nullptr;
	for (i = 1; i < friends.size(); i++) {
		temp = &friends.at(i);
		j = i - 1;
		while (j >= 0 && friends.at(j).getNameUser() > temp->getNameUser()) {
			friends.at(j + 1) = friends.at(j);
			j--;
		}
		friends.at(j + 1) = *temp;
	}
}

int MainSystem::queryUser(QString account)
{
	return 0;
}

int MainSystem::sendFriendRequest(QString account)
{
	return 0;
}

int MainSystem::deleteFriend(QString account)
{
	return 0;
}

int MainSystem::modifyUserInfo(QString nickname, QString area)
{
	QString u = QString("%1/user/info").arg(PREURL);
	QUrl url(u);
	QNetworkRequest request(url);
	//打包json
	QJsonObject json;
	json.insert("name", nickname);
	json.insert("area", area);
	//转为字节流
	QJsonDocument jsonDoc(json);
	QByteArray jsonData = jsonDoc.toJson();
	//设置请求头
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));
	QNetworkReply *reply = clientCore->sendPostRequset(request, jsonData);

	if (reply == nullptr)
		return -2;  //请求失败
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());

	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		if (json["code"].toInt() == 1) {    //修改成功
			systemUser->modifyInfo(nickname, area);
			delete reply;
			return 0;       //修改成功
		} else {
			qDebug() << "fail when modifyUserInfo";
			delete reply;
			return -8;      //修改失败
		}
	} else {
		qDebug() << "Login:  " << strReply;
		return -1;  //无法解析Json
	}
}
