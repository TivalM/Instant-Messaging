#include "pages/LoginDialog.h"
#include "pages/RegisterDialog.h"
#include "pages/MainDialog.h"
#include "ui_FunctionTitleBar.h"
#include "MainSystem.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginDialog l;
	RegisterDialog r;
	MainDialog m;
	//信号连接
	//用于界面间跳转的信号
	QObject::connect(&l, SIGNAL(showRegister()), &r, SLOT(receiveShow()));
	QObject::connect(&r, SIGNAL(showLogin()), &l, SLOT(receiveShow()));
	QObject::connect(&r, SIGNAL(hideLogin()), &l, SLOT(receiveHide()));
	QObject::connect(&l, SIGNAL(showMain()), &m, SLOT(receiveShow()));
	l.show();

	return a.exec();
}
