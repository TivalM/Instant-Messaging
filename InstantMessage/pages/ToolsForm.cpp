#include "pages/ToolsForm.h"
#include "ui_ToolsForm.h"
#include "ui_ListItemForm.h"

ToolsForm::ToolsForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);

	//工具页的第一页是个人信息，通过对联系人信息页进行修改完成
	userInfoForm = new SelfInfoForm();
	ui->horizontalLayout->addWidget(userInfoForm);
	ui->list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	connect(MainSystem::getSystem(),  SIGNAL(initSelfInfoWidgets()), this, SLOT(initial()));
}

void ToolsForm::initial()
{
	userInfoForm->loadSelfInfo();

	QFile file(":/src/css/SessionForm.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	}

	QListWidgetItem *header = nullptr;

	//加入第一个菜单项
	QWidget *w = new QWidget();
	//重构时应使用位置表达label
	Ui::ListItemForm *toolOne = new Ui::ListItemForm();
	toolOne->setupUi(w);
	toolOne->labelImg->resize(5, 5);
	toolOne->labelImg->setPixmap(QPixmap(":/src/image/toolOne.png"));
	toolOne->labelImg->setScaledContents(true);
	toolOne->labelName->setText(QString::fromLocal8Bit("个人信息"));
	toolOne->labelMotto->setVisible(false);

	header = new QListWidgetItem(ui->list);
	header->setSizeHint(QSize(ui->list->width(), 35));

	ui->list->addItem(header);
	ui->list->setItemWidget(header, w);
}

ToolsForm::~ToolsForm()
{
	delete ui;
}
