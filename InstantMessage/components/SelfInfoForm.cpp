#include "SelfInfoForm.h"

SelfInfoForm::SelfInfoForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PersonInfoForm)
{
	ui->setupUi(this);
}
void SelfInfoForm::loadSelfInfo()
{
	//从服务器请求数据
	ui->labelNickName->setText("Karl");
	ui->labelAccount->setText("12345");
	ui->labelHead->setPixmap(QPixmap(":/src/image/head.png"));
	ui->labelArea->setText(QString::fromLocal8Bit("未设置"));
	ui->btFunction->setText(QString::fromLocal8Bit("修改信息"));
	ui->editAccount->setVisible(false);
	ui->editArea->setVisible(false);
	ui->editName->setVisible(false);
}
SelfInfoForm::~SelfInfoForm()
{
	delete ui;
}

void SelfInfoForm::on_btFunction_clicked()
{
	QString command = ui->btFunction->text();
	if (command == QString::fromLocal8Bit("修改信息")) {
		ui->labelAccount->setVisible(false);
		ui->labelArea->setVisible(false);
		ui->labelNickName->setVisible(false);
		ui->editAccount->setPlaceholderText(ui->labelAccount->text());
		ui->editArea->setPlaceholderText(ui->labelArea->text());
		ui->editName->setPlaceholderText(ui->labelNickName->text());
		ui->editAccount->setVisible(true);
		ui->editArea->setVisible(true);
		ui->editName->setVisible(true);
		ui->btFunction->setText(QString::fromLocal8Bit("保存"));
	} else {
		QString name = ui->editAccount->text();
		QString area = ui->editArea->text();
		QString nickName = ui->editAccount->text();
		ui->labelAccount->setText(name);
		ui->labelArea->setText(area);
		ui->labelNickName->setText(nickName);
		ui->labelAccount->setVisible(true);
		ui->labelArea->setVisible(true);
		ui->labelNickName->setVisible(true);
		ui->editAccount->setVisible(false);
		ui->editArea->setVisible(false);
		ui->editName->setVisible(false);
		ui->btFunction->setText(QString::fromLocal8Bit("修改信息"));
	}
}
