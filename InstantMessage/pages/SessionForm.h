#ifndef SESSIONFORM_H
#define SESSIONFORM_H
#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include <QFile>
#include <vector>
#include "components/ListItemForm.h"
#include "components/ChatForm.h"
#include "MainSystem.h"
namespace Ui
{
class SessionForm;
}

class SessionForm : public QWidget
{
	Q_OBJECT

public:
	explicit SessionForm(QWidget *parent = nullptr);
	~SessionForm();
	void initial();
	void createOneSessionItem(int userid, QPixmap img, QString name);
	void refreshSessions();  //根据系统储存的列表申请信息
	void addAllSessionIntoList();
	Ui::SessionForm *getUi() const;

private:
	Ui::SessionForm *ui;
	ChatForm *chatForm;
	std::vector<ListItemForm *> sessionFormList;
	// 初始化控件;
	//  void initControl();

private slots:
	void putMessages(int listRow);
	void CreateOrTurnTo(QString);
//	void on_btSend_clicked();
};

#endif // SESSIONFORM_H
