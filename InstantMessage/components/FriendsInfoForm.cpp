#include "FriendsInfoForm.h"

FriendsInfoForm::FriendsInfoForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PersonInfoForm)
{
	ui->setupUi(this);
	ui->editAccount->setVisible(false);
	ui->editArea->setVisible(false);
	ui->editName->setVisible(false);
}

FriendsInfoForm::~FriendsInfoForm()
{
	delete ui;
}

void FriendsInfoForm::freshInfo(int friendId)
{
	MainSystem *system = MainSystem::getSystem();
	User *temp  = system->getFriendById(friendId);

	ui->labelNickName->setText(temp->getNameUser());
	ui->labelAccount->setText(temp->getAccountUser());
	ui->labelHead->setPixmap(*(temp->getHeadImg()));
	ui->labelHead->setScaledContents(true);
	ui->labelArea->setText(temp->getArea());
}

void FriendsInfoForm::on_btFunction_clicked()
{
	emit(toSession(ui->labelAccount->text()));
}
