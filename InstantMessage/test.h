#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <BaseWindow.h>

namespace Ui
{
class test;
}

class test : public BaseWindow
{
	Q_OBJECT

public:
	explicit test(QWidget *parent = nullptr);
	~test();

private:
	Ui::test *ui;
	void initTitleBar();
};

#endif // TEST_H
