#ifndef CONTACTFORM_H
#define CONTACTFORM_H
#pragma once
#include <QWidget>
#include <QLabel>
#include <vector>
#include <QFile>
#include "pages/PersonInfoForm.h"
#include "ui_SessionForm.h"
#include "ui_CharHeadForm.h"
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
	void initial();
	void freshInfo();
	void createOneFriend(int userid, QPixmap img, QString name);   //应当接受参数
	void loadSelectedPerson();
	void addAllFriendsIntoList();
	void sortFriends();
	~ContactForm();

private:
	//两页面使用同一个包含QListWidget的ui，重构时应重写为对基类的继承
	Ui::SessionForm *ui;
	PersonInfoForm *personInfoForm;
	std::vector<ListItemForm *> friendFormList;
};

#endif // CONTACTFORM_H
