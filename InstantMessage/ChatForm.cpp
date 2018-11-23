#include "ChatForm.h"
#include "ui_form.h"
#include <qdebug.h>
ChatForm::ChatForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChatForm)
{
	ui->setupUi(this);
}

ChatForm::~ChatForm()
{
	delete ui;
}
//加了这两个函数
void ChatForm::initControl()
{
	ui->pushButton_15->setIcon(QIcon(":/src/image/gerenziliao.png"));
	ui->pushButton_16->setIcon(QIcon(":/src/image/wenjianjia.png"));
	ui->pushButton_17->setIcon(QIcon(":/src/image/diandiandianshu.png"));
	ui->pushButton_9->setIcon(QIcon(":/src/image/biaoqing.png"));
	ui->pushButton_10->setIcon(QIcon(":/src/image/tupian.png"));
	ui->pushButton_11->setIcon(QIcon(":/src/image/yuyin.png"));
	ui->pushButton_12->setIcon(QIcon(":/src/image/wenjian.png"));
	ui->pushButton_13->setIcon(QIcon(":/src/image/jilu.png"));
	ui->pushButton_14->setIcon(QIcon(":/src/image/fasong.png"));

}

//2
void ChatForm::on_pushButton_14_clicked()
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

void ChatForm::on_label_linkActivated(const QString &link)
{

}
