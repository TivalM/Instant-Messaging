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
//	connect(ui->list, SIGNAL(currentRowChanged(int)), this, SLOT(putMessages(int)));
	initial();
}

SessionForm::~SessionForm()
{
	delete ui;
}

Ui::SessionForm *SessionForm::getUi() const
{
	return ui;
}

void SessionForm::putMessages(int listRow)
{
	//这个函数从系统中读取信息显示到控件上
	//判断这一行是哪一个会话
//	ListItemForm *item = (ListItemForm *)ui->list->item(listRow);
//	int sessionId = item->getId();
	//根据会话id提取信息并更新到控件上
}

void SessionForm::CreateOrTurnTo(QString account)
{
	//不良设计带来的冗杂
	MainSystem *system = MainSystem::getSystem();
	for (unsigned i = 0; i < sessionFormList.size(); i++) {
		if (system->getFriendById(system->getSessoinById(sessionFormList.at(i)->getId())
		                          .getParticipators().at(0))->getAccountUser() == account) {
			//已有一个与此人的对话,则转到
			ui->list->setCurrentRow(i);
			return;
		}
	}
	//没有此对话，则创建
	//是使用乐观刷新还是悲观刷新
	system->createASession(system->getFriendByAccount(account)->getIdUser());
	refreshSessions();
	ui->list->setCurrentRow(sessionFormList.size() - 1);
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
	refreshSessions();
}

void SessionForm::createOneSessionItem(int sessionId, QPixmap img, QString name)
{
	ListItemForm *p = new ListItemForm(this, sessionId, img, name);
	sessionFormList.push_back(p);
}

void SessionForm::refreshSessions()
{
	MainSystem *system = MainSystem::getSystem();
	//根据系统信息更新会话列表
	ui->list->clear();
	sessionFormList.clear();
	for (auto iter : system->getSessions()) {
		//系统储存的Session信息中不包括User本人
		User *participator  = system->getFriendById(iter.getParticipators().at(0));
		//Session 的 item使用服务器提供的SessionId作为Id
		createOneSessionItem(iter.getSessionId(), *(participator->getHeadImg()), participator->getNameUser());
	}
	addAllSessionIntoList();
}

void SessionForm::addAllSessionIntoList()
{
	for (unsigned int i = 0; i < sessionFormList.size(); i++) {
		QListWidgetItem *aitem = new QListWidgetItem(ui->list);
		aitem->setSizeHint(QSize(ui->list->width(), 50));
		ui->list->addItem(aitem);
		ui->list->setItemWidget(aitem, sessionFormList.at(i));
	}
}
