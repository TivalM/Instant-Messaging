#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#pragma once
#include <QDialog>
#include <QStackedWidget>
#include "components/BaseWindow.h"
#include "SessionForm.h"
#include "ContactForm.h"
#include "ToolsForm.h"
#include "pages/AddFriendsDialog.h"
#include "pages/InformDialog.h"

namespace Ui
{
class MainDialog;
}

class MainDialog : public BaseWindow
{
	Q_OBJECT

public:
	explicit MainDialog(QWidget *parent = nullptr, int windowType = 1);
	void initTitleBar();
	void loadUser();
	void updateFriendList();
	//信号连接暂不可用，手写切换函数

	~MainDialog();

private:
	Ui::MainDialog *ui;
	SessionForm *sessionForm;   //会话页面
	ContactForm *contactForm;   //联系人界面
	ToolsForm *toolsForm;       //工具箱界面

signals:
	void session(QString);

private slots:
	void receiveShow();     //收到由其它界面发送的信号时，该页面自主显示
	void showFriendRequest();
	void switchToSession();
	void switchToSession(QString);
	void switchToContact();
	void switchToTool();
	void openAddFriend();
};

#endif // MAINDIALOG_H
