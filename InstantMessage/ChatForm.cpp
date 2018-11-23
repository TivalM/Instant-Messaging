#include "ChatForm.h"
#include "ui_ChatForm.h"
#include <qdebug.h>
ChatForm::ChatForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChatForm)
{
	ui->setupUi(this);
	initControl();
}

ChatForm::~ChatForm()
{
	delete ui;
}
//加了这两个函数
void ChatForm::initControl()
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

//2
void ChatForm::on_btSend_clicked()
{
	QString content = ui->textEdit->toPlainText();    qDebug() << content.length();
	if (content.length() >= 3) {
		qDebug() << "进入了这个";
		QString s1 = "< img width='30' height='30' src='qrc:/src/image/head.png' "
		             "style='float:right;margin-left:15px;margin-right:15px;'>"
		             "<div style='background:rgb(205,215,226);padding-top:50px;float:right;"
		             "margin-top:10px;margin-right:45px;padding:50px;margin-left:400px;text-align:right;'>"
		             "<span style='font-size:17px;font-family:'Microsoft YaHei';margin-top:2px;'>"
		             + content + "</span>"
		             "</div><br><br>";
		ui->textBrowser->insertHtml(s1);
	} else {
		int flag = 60 + (24 - content.length()) * 15;
		QString myflag = QString::number(flag, 10);
		qDebug() << myflag;
		QString s1 = "< img width='30' height='30' src='qrc:/src/image/head.png' "
		             "style='float:right;margin-left:15px;margin-right:15px;'>"
		             "<div style='background:rgb(205,215,226);padding-top:8px;float:right;"
		             "margin-top:10px;margin-right:45px;padding:10px;margin-left:" + myflag + "px;'>";
		s1 += "<span style='font-size:17px;font-family:'Microsoft YaHei';margin-top:2px;'>" + content + "</span></div><br><br><br>";
		qDebug() << s1;
		ui->textBrowser->insertHtml(s1);
	}
	ui->textBrowser->moveCursor(QTextCursor::End); //ui->textEdit->clear();}
}
void ChatForm::on_label_linkActivated(const QString &link)
{

}
