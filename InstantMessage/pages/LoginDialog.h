#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#pragma once
#include <QMessageBox>
#include <QTableView>
#include <QIcon>
#include <QUrl>
#include "components/BaseWindow.h"

namespace Ui
{
class LoginDialog;
}

class LoginDialog : public BaseWindow
{
	Q_OBJECT

public:
	explicit LoginDialog(QWidget *parent = nullptr);
	void initTitleBar();
	void loadHeadImg();
	~LoginDialog();


private:
	Ui::LoginDialog *ui;

private slots:
	void receiveShow();     //收到由其它界面发送的信号时，该页面自主显示
	void receiveHide();
	void on_btRegister_clicked();
	void on_btLogin_clicked();

signals:
	void showRegister();    //显示注册页面
	void showMain();        //显示主页面
};

#endif // LOGINDIALOG_H
