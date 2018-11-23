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
	for (int i = 0; i < 15; i++) {
		formList[i] = new PerPersonForm;
		addOneFriend(i, QPixmap(":/src/image/head2.png"), "testFriend1", "There is a motto");
	}


//	Horizonta
	chatForm->setGeometry(216, 0, 400, 531);
	ui->horizontalLayout->addWidget(chatForm);

	ui->horizontalLayout->setStretch(0, 3);
	ui->horizontalLayout->setStretch(1, 10);
	ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
	chatForm->show();
	initControl();
}

SessionForm::~SessionForm()
{
	delete ui;
}

void SessionForm::initControl()
{
	ui->btPeerInfo->setIcon(QIcon(":/src/image/peerInfo.png"));
	ui->btMore->setIcon(QIcon(":/src/image/more.png"));
	ui->btEmoji->setIcon(QIcon(":/src/image/emoji.png"));
	ui->btImg->setIcon(QIcon(":/src/image/img.png"));
	ui->btRecording->setIcon(QIcon(":/src/image/recording.png"));
	ui->btFile->setIcon(QIcon(":/src/image/file.png"));
	ui->btHistory->setIcon(QIcon(":/src/image/history.png"));
	ui->btSend->setIcon(QIcon(":/src/image/send.png"));
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

void SessionForm::on_btSend_clicked()
{
	QString content = ui->textEdit->toPlainText();
	qDebug() << content.length();
	if (content.length() >= 23) {
		qDebug() << "进入了这个";
		QString s1 = "<img width='30' height='30' src='qrc:/src/image/head.png' style='float:right;margin-left:15px;margin-right:15px;'><div style='background:rgb(205,215,226);padding-top:8px;float:right;margin-top:10px;margin-right:45px;padding:10px;margin-left:60px;'><span style='font-size:15px;font-family:'Microsoft YaHei';margin-top:2px;'>" + content + "</span></div><br><br><br>";
		ui->textBrowser->insertHtml(s1);
	} else {
		int flag = 60 + (24 - content.length()) * 15;
		QString myflag = QString::number(flag, 10);;
		qDebug() << myflag;
		QString s1 = "<img width='30' height='30' src='qrc:/src/image/head.png' style='float:right;margin-left:15px;margin-right:15px;'><div style='background:rgb(205,215,226);padding-top:8px;float:right;margin-top:10px;margin-right:45px;padding:10px;margin-left:" + myflag + "px;'>";
		s1 += "<span style='font-size:15px;font-family:'Microsoft YaHei';margin-top:2px;'>" + content + "</span></div><br><br><br>";
		qDebug() << s1;
		ui->textBrowser->insertHtml(s1);
	}
	ui->textBrowser->moveCursor(QTextCursor::End);
	//ui->textEdit->clear();
}
