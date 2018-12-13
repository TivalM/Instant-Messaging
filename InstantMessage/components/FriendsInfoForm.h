#ifndef FRIENDSINFOFORM_H
#define FRIENDSINFOFORM_H

#include <QWidget>
#include "ui_PersonInfoForm.h"
#include "MainSystem.h"
namespace Ui
{
class FriendsInfoForm;
}

class FriendsInfoForm : public QWidget
{
	Q_OBJECT

public:
	explicit FriendsInfoForm(QWidget *parent = nullptr);
	~FriendsInfoForm();

private:
	Ui::PersonInfoForm *ui;

signals:
	void toSession(QString);

private slots:
	void freshInfo(int);       //联系人页中刷新联系人信息调用此函数
	void on_btFunction_clicked();
};

#endif // FRIENDSINFOFORM_H
