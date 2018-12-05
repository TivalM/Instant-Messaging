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

QNetworkReply *ClientCore::sendGetRequset(QUrl &url)
//互斥处理未定
{
	QNetworkReply *reply;
	QEventLoop loop;
	QTimer timer;
	timer.setInterval(RETRYTIME);   // 设置超时时间 8 秒
	timer.setSingleShot(true);      // 单次触发
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//异步发起请求
	QNetworkRequest request;
	request.setUrl(url);
	int total = 1;
	while (total <= 3) {
//		getMutex.lock();
		reply = manager->get(request);
		total++;
		timer.start();
		loop.exec();    //八秒后或接收到finished信号后退出
		if (timer.isActive() && reply->error() == QNetworkReply::NoError) { //请求完成
//			getMutex.unlock();
			return reply;
		} else {        //超时或错误
			if (timer.isActive()) {
				timer.stop();
				qDebug() << "POST: time out";
			}
			qDebug() << "POST: wrong";
			reply->abort();
			delete reply;
		}
	}
	qDebug() << "GET: fail";
	return nullptr;
}


QNetworkReply *ClientCore::sendPostRequset(QNetworkRequest postRequest, QByteArray jsonDate)
{
	QNetworkReply *reply;
	QEventLoop loop;
	QTimer timer;
	timer.setInterval(RETRYTIME);   // 设置超时时间 8 秒
	timer.setSingleShot(true);      // 单次触发
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//异步发起请求
	int total = 1;
	while (total <= 3) {
		reply = manager->post(postRequest, jsonDate);
		total++;
		timer.start();
		loop.exec();    //八秒后或接收到finished信号后退出
		if (timer.isActive() && reply->error() == QNetworkReply::NoError) { //请求完成
			return reply;
		} else {         //超时或错误
			if (timer.isActive()) {
				timer.stop();
				qDebug() << "POST: time out";
			}
			qDebug() << "POST: wrong";
			reply->abort();
			delete reply;
		}
	}
	qDebug() << "POST: fail";
	return nullptr;
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
