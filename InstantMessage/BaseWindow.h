#ifndef BASECLASS_H
#define BASECLASS_H

#include <QDialog>
#include "TitleBar.h"
class BaseWindow : public QDialog
{
	Q_OBJECT

public:
	explicit BaseWindow(QWidget *parent = nullptr);
	~BaseWindow();

private:
	void initTitleBar();
	void paintEvent(QPaintEvent *event);
	void loadStyleSheet(const QString &sheetName);

private slots:
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

protected:
	TitleBar *titleBarPtr;

};

#endif // BASECLASS_H
