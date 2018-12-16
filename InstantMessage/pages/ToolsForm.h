﻿#ifndef TOOLSFORM_H
#define TOOLSFORM_H

#include <QWidget>
#include <QLabel>
#include <vector>
#include <QFile>
#include "MainSystem.h"
#include "components/SelfInfoForm.h"
#include "ui_SessionForm.h"
#include "components/ListItemForm.h"

namespace Ui
{
class ToolsForm;
}

class ToolsForm : public QWidget
{
	Q_OBJECT

public:
	explicit ToolsForm(QWidget *parent = nullptr);
	void freshInfo();
	~ToolsForm();

private:
	//页面共用包含QListWidget的ui，重构时应重写为对基类的继承
	//个人信息页由联系人信息页修改而来
	Ui::SessionForm *ui;
	SelfInfoForm *userInfoForm;
public slots:
	void initial();
};

#endif // TOOLSFORM_H
