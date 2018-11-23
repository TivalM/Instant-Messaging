#ifndef PERPERSONFORM_H
#define PERPERSONFORM_H
#pragma once
#include <QWidget>
#include <QPixmap>

namespace Ui
{
class PerPersonForm;
}

class PerPersonForm : public QWidget
{
	Q_OBJECT

public:
	explicit PerPersonForm(QWidget *parent = nullptr);
	void initial(QPixmap img, QString name, QString motto = "");

	~PerPersonForm();

	QString getName() const;

private:
	QPixmap headImg;
	QString name;
	QString personalMotto;
	Ui::PerPersonForm *ui;
};

#endif // PERPERSONFORM_H
