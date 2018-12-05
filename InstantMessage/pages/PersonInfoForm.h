#ifndef PERSONINFOFORM_H
#define PERSONINFOFORM_H
#pragma once
#include <QWidget>
#include "MainSystem.h"
#include "User.h"
namespace Ui
{
class PersonInfoForm;
}

class PersonInfoForm : public QWidget
{
	Q_OBJECT

public:
	explicit PersonInfoForm(QWidget *parent = nullptr);
	void loadSelfInfo();    //工具页中作为个人信息页调用此函数
	~PersonInfoForm();

private:
	Ui::PersonInfoForm *ui;

signals:
	void toSession(QString);

private slots:
	void freshInfo(int);       //联系人页中刷新联系人信息调用此函数

	void on_btToSession_clicked();
};

#endif // PERSONINFOFORM_H
