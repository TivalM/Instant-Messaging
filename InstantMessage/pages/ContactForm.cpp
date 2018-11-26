#include "pages/ContactForm.h"
#include "ui_ListItemForm.h"
#include <QDebug>
ContactForm::ContactForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);
	//在右边插入信息页，该信息页随着选择的联系人的不同而刷新
	personInfoForm = new PersonInfoForm();
	ui->horizontalLayout->addWidget(personInfoForm);
	ui->list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	initial();
}


ContactForm::~ContactForm()
{
	delete ui;
}

void ContactForm::initial()
{
	QFile file(":/src/css/SessionForm.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	}

	createOneFriend(0, QPixmap(":/src/image/head2.png"), "Core");
	createOneFriend(1, QPixmap(":/src/image/head3.png"), "Karl");
	createOneFriend(2, QPixmap(":/src/image/head4.png"), "Macy");
	createOneFriend(3, QPixmap(":/src/image/head5.png"), "Tanya");
	createOneFriend(4, QPixmap(":/src/image/head6.png"), "Terry");
	createOneFriend(5, QPixmap(":/src/image/head7.png"), "Able");
	createOneFriend(6, QPixmap(":/src/image/head8.png"), "Jocelyn");
	sortFriends();
	addAllFriendsIntoList();
	connect(ui->list, SIGNAL(currentRowChanged(int)), personInfoForm, SLOT(freshInfo()));
}

void ContactForm::freshInfo()
{

}

void ContactForm::createOneFriend(int userid, QPixmap img, QString name)
{
	ListItemForm *p = new ListItemForm(this, userid, img, name);
	friendFormList.push_back(p);
}

void ContactForm::loadSelectedPerson()
{

}

void ContactForm::addAllFriendsIntoList()
{
	QChar divide = ' ';
	for (unsigned int i = 0; i < friendFormList.size(); i++) {
		//出现新字母
		if (divide != friendFormList.at(i)->getName().at(0).toUpper()) {
			divide = friendFormList.at(i)->getName().at(0).toUpper();
			QListWidgetItem *header = nullptr;

			QWidget *w = new QWidget();
//			Ui::CharHeadForm *charForm = new Ui::CharHeadForm();
			//重构时应使用位置表达label
			Ui::ListItemForm *charForm = new Ui::ListItemForm();
			charForm->setupUi(w);
			charForm->labelImg->setText(divide);
			header = new QListWidgetItem(ui->list);
			header->setSizeHint(QSize(ui->list->width(), 35));

			ui->list->addItem(header);
			ui->list->setItemWidget(header, w);
		}
		//    layout->add
		QListWidgetItem *aitem = new QListWidgetItem(ui->list);
		aitem->setSizeHint(QSize(ui->list->width(), 50));
		ui->list->addItem(aitem);
		ui->list->setItemWidget(aitem, friendFormList.at(i));

	}
}

void ContactForm::sortFriends()
{
	//按字典序比较并排序
	//转为unsigned int可以解除警告
	int i, j;
	ListItemForm *temp = nullptr;
	for (i = 1; i < 7; i++) {
		temp = friendFormList.at(i);
		j = i - 1;
		while (j >= 0 && friendFormList.at(j)->getName() > temp->getName()) {
			friendFormList.at(j + 1) = friendFormList.at(j);
			j--;
		}
		friendFormList.at(j + 1) = temp;
	}
}

