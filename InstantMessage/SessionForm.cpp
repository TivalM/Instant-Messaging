#include "SessionForm.h"
#include "ui_SessionForm.h"
#include <QDebug>
#define BUTTON_HEIGHT 20        // 按钮高度;
#define BUTTON_WIDTH 20         // 按钮宽度;


SessionForm::SessionForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);
	chatForm = new ChatForm(this);
	ui->horizontalLayout->addWidget(chatForm);
	for (int i = 0; i < 15; i++) {
		formList[i] = new PerPersonForm;
		addOneFriend(i, QPixmap(":/src/image/head2.png"), "testFriend1", "There is a motto");
	}
	ui->friendList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	loadStyleSheet("SessionForm");
//	initControl();
}

void SessionForm::loadStyleSheet(const QString &sheetName)
{
	QFile file("G:\\GitHub\\Instant-Messaging\\InstantMessage\\css\\" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	} else
		qDebug() << "No such file";
}

SessionForm::~SessionForm()
{
	delete ui;
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
