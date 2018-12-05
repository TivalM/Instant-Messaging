#include "pages/RegisterDialog.h"
#include "ui_RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
	BaseWindow(parent),
	ui(new Ui::RegisterDialog)
{
	ui->setupUi(this);
	//设置背景
	// 初始化标题栏;
	this->initTitleBar();
	this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window,
	                 QBrush(QPixmap(":/src/image/login_background.png").scaled(// 缩放背景图.
	                                this->size(),
	                                Qt::IgnoreAspectRatio,
	                                Qt::SmoothTransformation)));    // 使用平滑的缩放方式
	this->setPalette(palette);                                      // 给widget加上背景图


	//设置输入框icon
	ui->editAccount->addAction(QIcon(":/src/image/user.png"), QLineEdit::LeadingPosition);
	ui->editPassword->addAction(QIcon(":/src/image/lock.png"), QLineEdit::LeadingPosition);
	ui->editConfirm->addAction(QIcon(":/src/image/confirm.png"), QLineEdit::LeadingPosition);
	ui->editNickname->addAction(QIcon(":/src/image/mail.png"), QLineEdit::LeadingPosition);

	//设置输入提示
	ui->editAccount->setPlaceholderText(QString::fromLocal8Bit("用户名是唯一的、用于登陆的凭证。"));
	ui->editPassword->setPlaceholderText(QString::fromLocal8Bit("长度为6至18位，空格会被忽略"));
	ui->editConfirm->setPlaceholderText(QString::fromLocal8Bit("请重复输入密码"));
	ui->editNickname->setPlaceholderText(QString::fromLocal8Bit("邮箱是用于找回密码的凭证"));
}

void RegisterDialog::initTitleBar()
{
	titleBarPtr->setButtonType(MIN_BUTTON);
	titleBarPtr->setTitleWidth(this->width());
	titleBarPtr->setBackgroundColor(219, 219, 255);
	titleBarPtr->setTitleContent(QString::fromLocal8Bit("注册"));
}

RegisterDialog::~RegisterDialog()
{
	delete ui;
}

void RegisterDialog::receiveShow()
{
	this->show();
	emit hideLogin();
}

void RegisterDialog::on_btRegister_clicked()
{
	bool debug = true;
	if (!debug) {
		MainSystem *system = MainSystem::getSystem();
		//收集数据
		QString account = ui->editAccount->text();
		QString password = ui->editPassword->text();
		QString confirm = ui->editConfirm->text();
		QString nickName = ui->editNickname->text();
		int state = system->signUp(account, password, nickName);
		//判定
		if (state == 0) {
			//若返回值为0，说明账号已成功创建并储存
			QMessageBox::information(this, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("注册成功"));
			emit showLogin();
			this->close();
		} else if (state == -3)
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("该账号已经存在"));
		else {
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("在载入过程中出现网络连接错误"));
		}
	} else {
		emit showLogin();
		this->close();
	}
}
