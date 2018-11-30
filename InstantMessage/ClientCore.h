#ifndef CLIENTCORE_H
#define CLIENTCORE_H
#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QtWebSockets/QtWebSockets>
#include <QTimer>
#include <vector>
#include <QEventLoop>

enum {};
#define RETRYTIME 8000
class ClientCore : public QObject
{
	Q_OBJECT

public:
	ClientCore(QObject *parent = nullptr);
	int initWebSocket(const QUrl &url);
	QNetworkReply *sentGetRequset(QUrl &url);
	QWebSocket &getWebSocket();
	QUrl getSocketUrl() const;
	QNetworkAccessManager *getManager() const;

signals:
	void closed();
	void forceOut();    //无法连接服务器时，强制登出

private:
	QNetworkAccessManager *manager;
	QNetworkRequest request;
	QNetworkReply *reply;
	QWebSocket webSocket;       //这个webSocket用于接受消息推送
	QTimer timer;
	QUrl socketUrl;
	int totalFailTimes;         //总尝试连接次数


private slots:
	void onConnected();     //成功以WebSockets连接服务器后
	void onDisconnected();  //WebSockets连接断开后
	void reconnect();
	void onTextMessageReceived(QString message);
	QString managerFinished(QNetworkReply *reply);

};

#endif // CLIENTCORE_H
