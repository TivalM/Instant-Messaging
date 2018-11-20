#include "SessionForm.h"
#include "ui_SessionForm.h"

SessionForm::SessionForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);
}

void SessionForm::refreshFriends()
{

}

SessionForm::~SessionForm()
{
	delete ui;
}
