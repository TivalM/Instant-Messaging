#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#pragma once
#include <QDialog>
#include <QStackedWidget>
#include "BaseWindow.h"
#include "SessionForm.h"
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
	~MainDialog();

private:
	Ui::MainDialog *ui;
	QWidget *sessionForm;           //会话页面

private slots:
	void receiveShow();     //收到由其它界面发送的信号时，该页面自主显示
};

#endif // MAINDIALOG_H
