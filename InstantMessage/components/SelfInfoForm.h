#ifndef SELFINFOFORM_H
#define SELFINFOFORM_H

#include <QWidget>
#include "ui_PersonInfoForm.h"
#include "MainSystem.h"
namespace Ui
{
class SelfInfoForm;
}

class SelfInfoForm : public QWidget
{
	Q_OBJECT

public:
	explicit SelfInfoForm(QWidget *parent = nullptr);
	void loadSelfInfo();
	~SelfInfoForm();

private:
	Ui::PersonInfoForm *ui;

signals:

private slots:
	void on_btFunction_clicked();
};

#endif // SELFINFOFORM_H
