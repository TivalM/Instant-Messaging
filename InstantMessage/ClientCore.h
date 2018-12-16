#ifndef CLIENTCORE_H
#define CLIENTCORE_H
#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QtWebSockets/QtWebSockets>
#include <QTimer>
#include <vector>
#include <QEventLoop>
#define PREURL "http://120.78.120.65:8080"

enum {};
#define RETRYTIME 5000
class ClientCore : public QObject
{
	Q_OBJECT

public:
	ClientCore(QObject *parent = nullptr);
	int initWebSocket(const QUrl &url);
	QNetworkAccessManager *getManager() const;
	QNetworkReply *sendGetRequset(QNetworkRequest &getRequest);
	QNetworkReply *sendPostRequset(QNetworkRequest &postRequest, QByteArray &jsonDate);
	QWebSocket &getWebSocket();
	QNetworkCookie getCookie();
	QUrl getSocketUrl() const;
	int sendByWebSocket(QByteArray data);


signals:
	void closed();
	void forceOut();    //无法连接服务器时，强制登出

private:
	QNetworkAccessManager *manager;
	QNetworkCookie cookie;
	QWebSocket webSocket;       //这个webSocket用于接受消息推送
	QTimer timer;
	QUrl socketUrl;
	int totalFailTimes;         //总尝试连接次数

private slots:
	void onConnected();     //成功以WebSockets连接服务器后
	void onDisconnected();  //WebSockets连接断开后
	void reconnect();
	void onTextMessageReceived(QString message);
};

#endif // CLIENTCORE_H
