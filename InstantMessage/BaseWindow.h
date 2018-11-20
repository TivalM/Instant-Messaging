#ifndef BASECLASS_H
#define BASECLASS_H
#pragma once
#include <QDialog>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include "TitleBar.h"
class BaseWindow : public QDialog
{
	Q_OBJECT

public:
	explicit BaseWindow(QWidget *parent = nullptr,  int windowType = 0);
	~BaseWindow();

private:
	void initTitleBar(int type);
	void paintEvent(QPaintEvent *event);
	void loadStyleSheet(const QString &sheetName);


private slots:
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

protected:
	TitleBar *titleBarPtr;
	void resizeEvent(QResizeEvent *event);



};

#endif // BASECLASS_H
