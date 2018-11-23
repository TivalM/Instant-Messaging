#include "PerPersonForm.h"
#include "ui_PerPersonForm.h"

PerPersonForm::PerPersonForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PerPersonForm)
{
	ui->setupUi(this);
}

void PerPersonForm::initial(QPixmap img, QString name, QString motto)
{
	headImg = img;
	this->name = name;
	personalMotto = motto;

	ui->labelImg->setPixmap(img);
	ui->labelImg->setScaledContents(true);
	ui->labelName->setText(name);
	if (motto != "")
		ui->labelMotto->setText(motto);
	else
		ui->labelMotto->setVisible(false);
}

PerPersonForm::~PerPersonForm()
{
	delete ui;
}

QString PerPersonForm::getName() const
{
	return name;
}
