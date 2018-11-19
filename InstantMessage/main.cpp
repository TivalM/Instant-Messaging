#include "LoginDialog.h"
#include "RegisterDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginDialog l;
	RegisterDialog r;
	//信号连接
	//用于界面间跳转的信号
	QObject::connect(&l, SIGNAL(showRegister()), &r, SLOT(receiveShow()));
	QObject::connect(&r, SIGNAL(showLogin()), &l, SLOT(receiveShow()));
	l.show();
	return a.exec();
}
