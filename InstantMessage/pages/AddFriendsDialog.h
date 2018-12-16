#ifndef ADDFRIENDSDIALOG_H
#define ADDFRIENDSDIALOG_H

#pragma once
#include <QMessageBox>
#include <QTableView>
#include <QIcon>
#include <QUrl>
#include "MainSystem.h"
#include "components/BaseWindow.h"

namespace Ui
{
class AddFriendsDialog;
}

class AddFriendsDialog : public BaseWindow
{
	Q_OBJECT

public:
	explicit AddFriendsDialog(QWidget *parent = nullptr);
	~AddFriendsDialog();
	void initTitleBar();

private slots:
	void on_searchBtn_clicked();
	void on_sendBtn_clicked();

private:
	Ui::AddFriendsDialog *ui;
};

#endif // ADDFRIENDSDIALOG_H
