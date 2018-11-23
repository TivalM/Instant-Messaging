#ifndef CONTACTFORM_H
#define CONTACTFORM_H
#pragma once
#include <QWidget>
#include <QLabel>
#include "ui_SessionForm.h"
#include "ui_CharHeadForm.h"
#include "PerPersonForm.h"

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
	void createOneFriend(int i, QPixmap img, QString name);   //应当接受参数
	void addAllFriends();
	void sortFriends();
	~ContactForm();

private:
	//两页面使用同一个包含QListWidget的ui，重构时应重写为对基类的继承
	Ui::SessionForm *ui;
	//for now
	PerPersonForm *formList[20];
};

#endif // CONTACTFORM_H
