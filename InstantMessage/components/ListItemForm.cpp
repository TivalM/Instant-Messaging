#include "components/ListItemForm.h"
#include "ui_ListItemForm.h"

ListItemForm::ListItemForm(QWidget *parent, int userId, QPixmap img, QString name, QString motto):
	QWidget(parent),
	ui(new Ui::ListItemForm)
{
	ui->setupUi(this);
	this->headImg = img;
	this->name = name;
	this->userId = userId;
	this->personalMotto = motto;

	ui->labelImg->setPixmap(img);
	ui->labelImg->setScaledContents(true);
	ui->labelName->setText(name);
	if (motto != "")
		ui->labelMotto->setText(motto);
	else
		ui->labelMotto->setVisible(false);
}

ListItemForm::~ListItemForm()
{
	delete ui;
}

QString ListItemForm::getName() const
{
	return name;
}

int ListItemForm::getUserId() const
{
	return userId;
}
