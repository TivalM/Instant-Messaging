﻿#include "User.h"

User::User(QString account, int state)
{
	this->accountUser = account;
	this->state  = state;
}

User::User(int id, QString name, QString account, QString area, QPixmap *headImg, int state)
{
	this->idUser = id;
	this->accountUser = account;
	this->nameUser = name;
	this->state = state;
	this->area = area;
	this->headImg = headImg;
}

int User::getIdUser() const
{
	return idUser;
}

int User::setInfo(int id, QString name, QString area, QPixmap *headImg)
{
	this->idUser = id;
	this->nameUser = name;
	this->area = area;
	this->headImg = headImg;
	return 0;
}

int User::modifyInfo(QString name, QString area)
{
	this->nameUser = name;
	this->area = area;
	return 0;
}

QString User::getNameUser() const
{
	return nameUser;
}

QString User::getAccountUser() const
{
	return accountUser;
}

QPixmap *User::getHeadImg() const
{
	return headImg;
}

QString User::getArea() const
{
	return area;
}



int User::getState() const
{
	return state;
}
