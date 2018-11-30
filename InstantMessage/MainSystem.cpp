#include "MainSystem.h"

MainSystem *MainSystem::mainSystem = nullptr;

MainSystem::MainSystem()
{
	clientCore = new ClientCore();
	//预留空间
	friends.reserve(16);
	sessions.reserve(8);
}

int MainSystem::getFriendInfoById(int id)
{
	return 0;
}

Session &MainSystem::getSessoinById(unsigned int id)
{
	return sessions.at(id);
}

int MainSystem::getUserInfo(QString account)
{
	return 0;
}

int MainSystem::signUp(QString account, QString password, QString nickname)
{
	QString u = QString("%1/user/login?account=%2&password=%3").arg(PREURL).arg(account).arg(password);
	QUrl url(u);
	QNetworkReply *reply = clientCore->sentGetRequset(url);
	return 0;
}

int MainSystem::login(QString account, QString password)
{
	QString u = QString("%1/user/login?account=%2&password=%3").arg(PREURL).arg(account).arg(password);
	QUrl url(u);
	QNetworkReply *reply = clientCore->sentGetRequset(url);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
	QJsonDocument jsonReply = QJsonDocument::fromJson(strReply.toUtf8());

	if (!jsonReply.isNull()) {
		//成功解析
		QJsonObject json = jsonReply.object();
		systemUser = new User(account);
		if (json["code"].toInt() == 1) {    //登陆成功
			//请求该系统用户的其它信息
			loadUserInfo();
			clientCore->initWebSocket(QUrl(QString("ws://%1/webSocket/%2").arg(PREURL).arg("1")));
		}
		return 0;
	} else {
		qDebug() << "Login:  " << strReply;
		return -1;  //无法解析Json
	}
}

int MainSystem::loadUserInfo()
{
	QUrl url(QString("%1/user/info").arg(PREURL));
	QNetworkReply *reply = clientCore->sentGetRequset(url);
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
				qDebug() << "can not load headimg " << data["userId"].toInt();
			}
			//用户id尚不存在
			systemUser->loadInfo(data["userId"].toInt(), data["name"].toString(), data["area"].toString(), img);
			//得知登录的用户后初始化websocket连接
			clientCore->initWebSocket(QUrl(QString("ws://%1/webSocket/%2").arg(PREURL).arg(data["userId"].toInt())));
		}
		return 0;
	} else {
		qDebug() << "LoadUserInfo:  " << strReply;
		return -1;  //无法解析Json
	}
}

int MainSystem::loadFriendList()
{
	QUrl url(QString("%1/user/friendList").arg(PREURL));
	QNetworkReply *reply = clientCore->sentGetRequset(url);
	if (reply == nullptr)
		return -2;
	//解析
	QString strReply = QString::fromStdString(reply->readAll().toStdString());
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
		}
		return 0;
	} else {
		qDebug() << "LoadUserInfo:  " << strReply;
		return -1;
	}
}

int MainSystem::loadSessions()
{
	QUrl url(QString(""));
	QNetworkReply *reply = clientCore->sentGetRequset(url);
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
	QNetworkReply *reply = clientCore->sentGetRequset(url);
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
				Session sessionNow = sessions.at(index);
				QJsonObject data = json["data"].toObject();
				//获取消息列表
				QJsonArray list = data["list"].toArray();
				for (auto iter : list) {
					//对于每一条消息字段
					QJsonObject element = iter.toObject();
					sessionNow.insertMessage(element["sender"].toInt(), element["time"].toDa)
				}
			}

		}

	} else {
		qDebug() << "LoadUserInfo:  " << strReply;
		return -1;
	}
}

QPixmap *MainSystem::loadImg(int id)
{
	QPixmap *img = new QPixmap();
	QUrl url(QString("%1/static/image/%2.jpg").arg(PREURL).arg(id));
	QNetworkReply *reply = clientCore->sentGetRequset(url);
	qDebug() << "Load Img" << id;
	if (img->loadFromData(reply->readAll()))
		return img;
	delete img;
	return nullptr;
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
	return 0;
}

MainSystem *MainSystem::getMainSystem()
{
	return mainSystem;
}
