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
	~PersonInfoForm();

private:
	Ui::PersonInfoForm *ui;

private slots:
	void freshInfo();
};

#endif // PERSONINFOFORM_H
