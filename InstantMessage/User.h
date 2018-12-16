#ifndef USER_H
#define USER_H
#pragma once
#include <QString>
#include <QPixmap>

class User
{
public:
	explicit User(QString account, int state = 0);//这个构造函数在初始化系统用户时使用
	explicit User(int id, QString name, QString account, QString area, QPixmap *headImg = nullptr, int state = 0); //这个构造函数用于构造好友用户
	int setInfo(int id, QString name, QString area, QPixmap *headImg = nullptr);       //载入用户信息
	int modifyInfo(QString name, QString area);
	int getState() const;
	int getIdUser() const;
	QString getNameUser() const;
	QString getAccountUser() const;
	QPixmap *getHeadImg() const;
	QString getArea() const;

private:
	int idUser;
	int state;
	QString nameUser;
	QString accountUser;
	QString area;
	QPixmap *headImg = nullptr;
};


#endif // USER_H
