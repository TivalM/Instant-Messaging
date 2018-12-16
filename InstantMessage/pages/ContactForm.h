#ifndef CONTACTFORM_H
#define CONTACTFORM_H
#pragma once
#include <QWidget>
#include <QLabel>
#include <vector>
#include <QFile>
#include "MainSystem.h"
#include "components/FriendsInfoForm.h"
#include "ui_SessionForm.h"
#include "components/ListItemForm.h"

namespace Ui
{
class ContactForm;
}

class ContactForm : public QWidget
{
	Q_OBJECT

public:
	explicit ContactForm(QWidget *parent = nullptr);
	~ContactForm();
	void getIdByIndex();
	void createOneFriendItem(int userid, QPixmap img, QString name);   //应当接受参数
	void refreshFriends();  //根据系统储存的列表申请信息
	void createASession();
	void loadSelectedPerson();
	void addAllFriendsIntoList();
	Ui::SessionForm *getUi() const;
	FriendsInfoForm *getFriendsInfoForm() const;

private:
	//两页面使用同一个包含QListWidget的ui，重构时应重写为对基类的继承
	Ui::SessionForm *ui;
	FriendsInfoForm *friendsInfoForm;
	std::vector<ListItemForm *> friendFormList;
signals:
	void freshInfoPage(int);

private slots:
	void getIdByIndex(int currIndex);
	void initial();
};

#endif // CONTACTFORM_H
