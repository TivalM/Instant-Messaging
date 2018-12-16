#ifndef INFORMDIALOG_H
#define INFORMDIALOG_H

#pragma once
#include <QMessageBox>
#include <QTableView>
#include <QIcon>
#include <QUrl>
#include "MainSystem.h"
#include "components/BaseWindow.h"
#include "components/InformListItemForm.h"
#include <QListWidgetItem>
#include <QFile>
#include <vector>

namespace Ui
{
class InformDialog;
}

class InformDialog : public BaseWindow
{
	Q_OBJECT

public:
	explicit InformDialog(QWidget *parent = 0);
	~InformDialog();
	void initTitleBar();
	void loadInformInfo();
	void addAllInformIntoList();
	void createOneInformItem(QPixmap img, QString name = "", QString content = "");
	void addInformIntoList();


private:
	Ui::InformDialog *ui;
	std::vector<InformListItemForm *> informFormList;
};

#endif // INFORMDIALOG_H
