#ifndef SESSIONFORM_H
#define SESSIONFORM_H
#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include "PerPersonForm.h"
#include "ChatForm.h"
namespace Ui
{
class SessionForm;
}

class SessionForm : public QWidget
{
	Q_OBJECT

public:
	explicit SessionForm(QWidget *parent = nullptr);
	void initial();
	void refreshFriends();  //根据系统好友列表申请信息
	void addOneFriend(int i, QPixmap img, QString name, QString motto = "");   //应当接受参数
	~SessionForm();

private:
	Ui::SessionForm *ui;
	ChatForm *chatForm;
	PerPersonForm *formList[20];


	// 初始化控件;
	void initControl();

private slots:
	void on_btSend_clicked();
};

#endif // SESSIONFORM_H
