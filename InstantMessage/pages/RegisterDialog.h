#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#pragma once
#include "components/BaseWindow.h"
#include "MainSystem.h"
#include <QMessageBox>
namespace Ui
{
class RegisterDialog;
}

class RegisterDialog : public BaseWindow
{
	Q_OBJECT

public:
	explicit RegisterDialog(QWidget *parent = nullptr);
	void initTitleBar();
	~RegisterDialog();

private slots:
	void receiveShow();             //收到由其它界面发送的信号时，该页面自主显示
	void on_btRegister_clicked();

signals:
	void showLogin();
	void hideLogin();

private:
	Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
