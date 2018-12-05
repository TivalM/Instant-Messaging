#include "components/ListItemForm.h"
#include "ui_ListItemForm.h"

ListItemForm::ListItemForm(QWidget *parent, int Id, QPixmap img, QString name, QString motto):
	QWidget(parent),
	ui(new Ui::ListItemForm)
{
	//要贯彻UI与数据分离的原则，重构时应使用id表示Item，将数据剥除
	ui->setupUi(this);
	this->headImg = img;
	this->name = name;
	this->Id = Id;
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

int ListItemForm::getId() const
{
	return Id;
}
