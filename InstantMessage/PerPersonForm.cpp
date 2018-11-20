#include "PerPersonForm.h"
#include "ui_PerPersonForm.h"

PerPersonForm::PerPersonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PerPersonForm)
{
    ui->setupUi(this);
}

PerPersonForm::~PerPersonForm()
{
    delete ui;
}
