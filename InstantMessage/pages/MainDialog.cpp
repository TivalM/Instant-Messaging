#include "pages/MainDialog.h"
#include "components/BaseWindow.h"
#include "ui_MainDialog.h"

MainDialog::MainDialog(QWidget *parent, int windowType) :
	BaseWindow(parent, windowType),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	initTitleBar();
	sessionForm = new SessionForm(this);
	contactForm = new ContactForm(this);
	toolsForm = new ToolsForm(this);
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::initTitleBar()
{
	titleBarPtr->setButtonType(MIN_MAX_BUTTON);
	titleBarPtr->setTitleWidth(this->width());
	titleBarPtr->setBackgroundColor(219, 219, 255);
	connect(titleBarPtr->getUI()->btSessions, SIGNAL(clicked()), this, SLOT(switchToSession()));
	connect(titleBarPtr->getUI()->btFriends, SIGNAL(clicked()), this, SLOT(switchToContact()));
	connect(titleBarPtr->getUI()->btTool, SIGNAL(clicked()), this, SLOT(switchToTool()));
}

void MainDialog::loadUser()
{

}

void MainDialog::switchToSession()
{
	ui->pages->setCurrentIndex(0);
}

void MainDialog::switchToContact()
{
	ui->pages->setCurrentIndex(1);
}

void MainDialog::switchToTool()
{
	ui->pages->setCurrentIndex(2);
}


void MainDialog::receiveShow()
{
	ui->pages->addWidget(sessionForm);
	ui->pages->addWidget(contactForm);
	ui->pages->addWidget(toolsForm);
	this->show();
}
