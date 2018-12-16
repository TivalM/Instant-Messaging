#include "pages/AddFriendsDialog.h"
#include "ui_AddFriendsDialog.h"

AddFriendsDialog::AddFriendsDialog(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::AddFriendsDialog)
{
    ui->setupUi(this);
    this->initTitleBar();
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/src/image/login_background.png").scaled(// 缩放背景图.
                                    this->size(),
                                    Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation)));    // 使用平滑的缩放方式

    this->setPalette(palette);

    ui->searchTxt->setPlaceholderText(QString::fromLocal8Bit("请输入要查找的账号"));
    ui->sendTxt->setPlaceholderText(QString::fromLocal8Bit("请输入请求内容"));

    ui->headImg->hide();
    ui->nameLabel->hide();
    ui->sendBtn->hide();
    ui->sendTxt->hide();
}

AddFriendsDialog::~AddFriendsDialog()
{
    delete ui;
}

void AddFriendsDialog::initTitleBar()
{
    titleBarPtr->setButtonType(MIN_BUTTON);
    titleBarPtr->setTitleWidth(this->width());
    titleBarPtr->setBackgroundColor(219, 219, 255);
    titleBarPtr->setTitleContent(QString::fromLocal8Bit("添加好友"));
}

void AddFriendsDialog::on_searchBtn_clicked()
{
    QString account = ui->searchTxt->text().remove(QRegExp("\\s"));  //去除空格
    //查找
    MainSystem *system = MainSystem::getSystem();

    //if查找到
    //获取头像、用户名

    QPixmap headImg;
    QString name;

    ui->headImg->show();
    ui->headImg->setPixmap(headImg);
    ui->nameLabel->show();
    ui->nameLabel->setText(name);

    ui->sendBtn->show();
    ui->sendTxt->show();

    //else
    //QMessageBox::information(this, QString::fromLocal8Bit("查找失败"), QString::fromLocal8Bit("未找到此用户"));


}

void AddFriendsDialog::on_sendBtn_clicked()
{
    QString content = ui->sendTxt->toPlainText();
    //发送请求

    QMessageBox::information(this, QString::fromLocal8Bit("发送成功"), QString::fromLocal8Bit("发送好友申请成功"));

    this->close();
}
