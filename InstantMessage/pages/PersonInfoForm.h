#ifndef PERSONINFOFORM_H
#define PERSONINFOFORM_H

#include <QWidget>

namespace Ui
{
class PersonInfoForm;
}

class PersonInfoForm : public QWidget
{
	Q_OBJECT

public:
	explicit PersonInfoForm(QWidget *parent = nullptr);
	void loadSelfInfo();    //工具页中作为个人信息页调用此函数
	~PersonInfoForm();

private:
	Ui::PersonInfoForm *ui;

private slots:
	void freshInfo();       //联系人页中刷新联系人信息调用此函数
};

#endif // PERSONINFOFORM_H
