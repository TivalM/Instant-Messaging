#ifndef LISTITEMFORM_H
#define LISTITEMFORM_H
#pragma once
#include <QWidget>
#include <QPixmap>

namespace Ui
{
class ListItemForm;
}

class ListItemForm : public QWidget
{
	Q_OBJECT

public:
	explicit ListItemForm(QWidget *parent, int userId, QPixmap img, QString name, QString motto = "");
//	void initial(QPixmap img, QString name, QString motto = "");
	~ListItemForm();
	QString getName() const;
	int getUserId() const;

private:
	int userId;
	QPixmap headImg;
	QString name;
	QString personalMotto;
	Ui::ListItemForm *ui;
};

#endif // LISTITEMFORM_H
