#include "ClientCore.h"

ClientCore::ClientCore(QObject *parent) :
	QObject(parent),  timer(), totalFailTimes(0)
{
	manager = new QNetworkAccessManager(this);
}


int ClientCore::initWebSocket(const QUrl &url)
{
	socketUrl = url;
	qDebug() << "WebSocket server:" << url;
	connect(&webSocket, &QWebSocket::connected, this, &ClientCore::onConnected);
	connect(&webSocket, &QWebSocket::disconnected, this, &ClientCore::onDisconnected);
	connect(&timer, SIGNAL(timeout()), this, SLOT(reconnect()));
	timer.start(100);
	return 0;
}

QNetworkReply *ClientCore::sendGetRequset(QNetworkRequest &request)
//互斥处理未定
{
	QNetworkReply *reply;
	QEventLoop loop;
	QTimer timer;
	timer.setInterval(RETRYTIME);   // 设置超时时间 8 秒
	timer.setSingleShot(true);      // 单次触发
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	//异步发起请求
	int total = 1;
	while (total <= 3) {
		reply = manager->get(request);
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		total++;
		timer.start();
		loop.exec();    //五秒后或接收到finished信号后退出
		if (reply->error() == QNetworkReply::NoError) { //请求完成
			return reply;
		} else {        //超时或错误
			if (timer.isActive()) {
				timer.stop();
				qDebug() << "GET: time out";
			}
			qDebug() << "GET: wrong";
			qDebug() << "GET: " << reply->error();
			reply->abort();
			delete reply;
		}
	}
	qDebug() << "GET: fail";
	return nullptr;
}


QNetworkReply *ClientCore::sendPostRequset(QNetworkRequest &postRequest, QByteArray &postData)
{
	QNetworkReply *reply;
	QEventLoop loop;
	QTimer timer;
	timer.setInterval(RETRYTIME);   // 设置超时时间 8 秒
	timer.setSingleShot(true);      // 单次触发
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	//异步发起请求
	int total = 1;
	while (total <= 3) {
		reply = manager->post(postRequest, postData);
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		total++;
		timer.start();
		loop.exec();    //三秒后或接收到finished信号后退出
		if (reply->error() == QNetworkReply::NoError) { //请求完成
			QString u = QString("%1/user/login").arg(PREURL);
			if (manager->cookieJar()->cookiesForUrl(QUrl(u)).size() > 0)
				cookie = manager->cookieJar()->cookiesForUrl(QUrl(u)).at(manager->cookieJar()->cookiesForUrl(QUrl(u)).size() - 1);
			return reply;
		} else {         //超时或错误
			qDebug() << reply->error();
			if (timer.isActive()) {
				timer.stop();
				qDebug() << "POST: time out";
			} else
				qDebug() << "POST: wrong";
			reply->abort();
			delete reply;
		}
	}
	qDebug() << "POST: fail";
	return nullptr;
}

QNetworkCookie ClientCore::getCookie()
{
	return cookie;
}

QUrl ClientCore::getSocketUrl() const
{
	return socketUrl;
}

int ClientCore::sendByWebSocket(QByteArray data)
{
	if (webSocket.isValid())
		webSocket.sendBinaryMessage(data);
	return 0;
}

QNetworkAccessManager *ClientCore::getManager() const
{
	return manager;
}

void ClientCore::onConnected()
{
	//成功连接时
	timer.stop();
	qDebug() << "WebSocket connected";
	totalFailTimes = 0;
}

void ClientCore::onDisconnected()
{
	qDebug() << "WebSocket disconnected";
	timer.start(2000); //一段时间后尝试重连
}

void ClientCore::reconnect()
{
	timer.stop();
	if (totalFailTimes > 5) {
		qDebug() << "Fail to connect";
		return;
	}
	qDebug() << "Try to connect";
	totalFailTimes++;
	webSocket.abort();
	timer.start(RETRYTIME);
	webSocket.open(socketUrl);
}

void ClientCore::onTextMessageReceived(QString message)
{
	//收到推送过来的信息后
}
