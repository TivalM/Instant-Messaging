#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
	BaseWindow(parent),
	ui(new Ui::test)
{
	ui->setupUi(this);
	// 初始化标题栏;
	this->initTitleBar();
}

test::~test()
{
	delete ui;
}

void test::initTitleBar()
{
	titleBarPtr->setButtonType(MIN_MAX_BUTTON);
	titleBarPtr->setTitleWidth(this->width());
}
