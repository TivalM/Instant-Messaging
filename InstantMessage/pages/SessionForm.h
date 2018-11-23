#ifndef SESSIONFORM_H
#define SESSIONFORM_H
#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include <QFile>
#include <vector>
#include "components/ListItemForm.h"
#include "components/ChatForm.h"

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
	void createOneFriendForm(int userid, QPixmap img, QString name);
	void refreshFriends();  //根据系统好友列表申请信息
	void addAllFriendsIntoList();
	~SessionForm();

private:
	Ui::SessionForm *ui;
	ChatForm *chatForm;
	std::vector<ListItemForm *> sessionFormList;


	// 初始化控件;
//	void initControl();

private slots:
//	void on_btSend_clicked();
};

#endif // SESSIONFORM_H
