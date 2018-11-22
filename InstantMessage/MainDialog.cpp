#include "MainDialog.h"
#include "BaseWindow.h"
#include "ui_MainDialog.h"

MainDialog::MainDialog(QWidget *parent, int windowType) :
	BaseWindow(parent, windowType),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	initTitleBar();
	sessionForm = new SessionForm(this);
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
}

void MainDialog::loadUser()
{

}


void MainDialog::receiveShow()
{
	ui->pages->addWidget(sessionForm);
	this->show();
}
