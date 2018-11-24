#include "pages/SessionForm.h"
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
	ui->list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	initial();
}

SessionForm::~SessionForm()
{
	delete ui;
}

void SessionForm::initial()
{
	QFile file(":/src/css/SessionForm.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	}

	createOneFriendForm(0, QPixmap(":/src/image/head2.png"), "Core");
	createOneFriendForm(1, QPixmap(":/src/image/head3.png"), "Karl");
	createOneFriendForm(2, QPixmap(":/src/image/head4.png"), "Macy");
	createOneFriendForm(3, QPixmap(":/src/image/head5.png"), "Tanya");
	createOneFriendForm(4, QPixmap(":/src/image/head6.png"), "Terry");
	createOneFriendForm(5, QPixmap(":/src/image/head7.png"), "Able");
	createOneFriendForm(6, QPixmap(":/src/image/head8.png"), "Jocelyn");
	addAllFriendsIntoList();
}

void SessionForm::createOneFriendForm(int userid, QPixmap img, QString name)
{
	ListItemForm *p = new ListItemForm(this, userid, img, name);
	sessionFormList.push_back(p);
}

void SessionForm::refreshFriends()
{
	//根据好友列表申请信息
	//
}

void SessionForm::addAllFriendsIntoList()
{
	for (unsigned int i = 0; i < sessionFormList.size(); i++) {
		QListWidgetItem *aitem = new QListWidgetItem(ui->list);
		aitem->setSizeHint(QSize(ui->list->width(), 50));
		ui->list->addItem(aitem);
		ui->list->setItemWidget(aitem, sessionFormList.at(i));

	}
}
