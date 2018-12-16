#include "InformDialog.h"
#include "ui_InformDialog.h"

InformDialog::InformDialog(QWidget *parent) :
	BaseWindow(parent),
	ui(new Ui::InformDialog)
{
	ui->setupUi(this);
	this->initTitleBar();
	ui->informlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	createOneInformItem(QPixmap(":/src/image/head7.png"), "Andy", QString::fromLocal8Bit("我是软件一班的同学"));
	addInformIntoList();
}

InformDialog::~InformDialog()
{
	delete ui;
}

void InformDialog::initTitleBar()
{
	titleBarPtr->setButtonType(MIN_BUTTON);
	titleBarPtr->setTitleWidth(this->width());
	titleBarPtr->setBackgroundColor(219, 219, 255);
	titleBarPtr->setTitleContent(QString::fromLocal8Bit("通知列表"));
}

void InformDialog::loadInformInfo()
{
	addAllInformIntoList();
}

void InformDialog::addAllInformIntoList()
{
	for (unsigned int i = 0; i < informFormList.size(); i++) {
		QListWidgetItem *aitem = new QListWidgetItem(ui->informlist);
		aitem->setSizeHint(QSize(ui->informlist->width(), 60));
		ui->informlist->addItem(aitem);
		ui->informlist->setItemWidget(aitem, informFormList.at(i));
	}
}

void InformDialog::createOneInformItem(QPixmap img, QString name, QString content)
{
	InformListItemForm *p = new InformListItemForm(this, img, name, content);
	informFormList.push_back(p);
}

void InformDialog::addInformIntoList()//增加一个ListItem
{
	int i = informFormList.size() - 1;
	QListWidgetItem *aitem = new QListWidgetItem(ui->informlist);
	aitem->setSizeHint(QSize(ui->informlist->width(), 60));
	ui->informlist->addItem(aitem);
	ui->informlist->setItemWidget(aitem, informFormList.at(i));
}
