#include "pages/ToolsForm.h"
#include "ui_ToolsForm.h"

ToolsForm::ToolsForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ToolsForm)
{
	ui->setupUi(this);
}

ToolsForm::~ToolsForm()
{
	delete ui;
}
