#include "pages/PersonInfoForm.h"
#include "ui_PersonInfoForm.h"

PersonInfoForm::PersonInfoForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PersonInfoForm)
{
	ui->setupUi(this);
}



PersonInfoForm::~PersonInfoForm()
{
	delete ui;
}

void PersonInfoForm::freshInfo()
{
	ui->labelNickName->setText("Karl");
	ui->labelAccount->setText("76895");
	ui->labelHead->setPixmap(QPixmap(":/src/image/head3.png"));
	ui->labelArea->setText(QString::fromLocal8Bit("广东-深圳"));

}
