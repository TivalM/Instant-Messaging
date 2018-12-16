#include "InformListItemForm.h"
#include "ui_InFormListItemForm.h"

InformListItemForm::InformListItemForm(QWidget *parent,QPixmap img,QString name,QString content) :
    QWidget(parent),
    ui(new Ui::InformListItemForm)
{
    ui->setupUi(this);
    this->head = img;
    this->name = name;
    this->content = content;

    ui->headImg->setPixmap(img);
    ui->headImg->setScaledContents(true);
    ui->nameLabel->setText(name);
    ui->contentLabel->setText(content);

}

InformListItemForm::~InformListItemForm()
{
    delete ui;
}

void InformListItemForm::on_agreeBtn_clicked()
{
    //同意请求
    ui->agreeBtn->hide();
    ui->rejectBtn->hide();
    ui->stateLabel->setText(QString::fromLocal8Bit("已同意"));
}

void InformListItemForm::on_rejectBtn_clicked()
{
    //拒绝请求
    ui->agreeBtn->hide();
    ui->rejectBtn->hide();
    ui->stateLabel->setText(QString::fromLocal8Bit("已拒绝"));
}
