#include "pages/PersonInfoForm.h"
#include "ui_PersonInfoForm.h"

PersonInfoForm::PersonInfoForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PersonInfoForm)
{
	ui->setupUi(this);
}

void PersonInfoForm::loadSelfInfo()
{
	ui->labelNickName->setText("Karl");
	ui->labelAccount->setText("12345");
	ui->labelHead->setPixmap(QPixmap(":/src/image/head.png"));
	ui->labelArea->setText(QString::fromLocal8Bit("未设置"));

	ui->btToSession->setText(QString::fromLocal8Bit("修改信息"));
}



PersonInfoForm::~PersonInfoForm()
{
	delete ui;
}

void PersonInfoForm::freshInfo(int friendId)
{
	MainSystem *system = MainSystem::getSystem();
	User *temp  = system->getFriendById(friendId);

	ui->labelNickName->setText(temp->getNameUser());
	ui->labelAccount->setText(temp->getAccountUser());
	ui->labelHead->setPixmap(*(temp->getHeadImg()));
	ui->labelArea->setText(temp->getArea());
}

void PersonInfoForm::on_btToSession_clicked()
{
	emit(toSession(ui->labelAccount->text()));
}
