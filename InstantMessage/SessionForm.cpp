#include "SessionForm.h"
#include "ui_SessionForm.h"

SessionForm::SessionForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);
	for (int i = 0; i < 15; i++) {
		formList[i] = new PerPersonForm;
		addOneFriend(i, QPixmap(":/src/image/head2.png"), "testFriend1", "There is a motto");
	}
}

void SessionForm::initial()
{
	//todo
	refreshFriends();

}

void SessionForm::refreshFriends()
{
	//根据好友列表申请信息
	//
}

void SessionForm::addOneFriend(int i, QPixmap img, QString name, QString motto)
{
	//在UI的好友列表中添加一个FriendForm
	formList[i]->initial(img, name, motto);
	QListWidgetItem *aitem = new QListWidgetItem(ui->friendList);
	aitem->setSizeHint(QSize(ui->friendList->width(), 50));
	ui->friendList->addItem(aitem);
	ui->friendList->setItemWidget(aitem, formList[i]);
}

SessionForm::~SessionForm()
{
	delete ui;
}
