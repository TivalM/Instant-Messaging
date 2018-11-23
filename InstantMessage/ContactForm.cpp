#include "ContactForm.h"

ContactForm::ContactForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SessionForm)
{
	ui->setupUi(this);
	initial();
}

void ContactForm::initial()
{
	for (int i = 0; i < 7; i++) {
		formList[i] = new PerPersonForm;
	}
	createOneFriend(0, QPixmap(":/src/image/head2.png"), "Core");
	createOneFriend(1, QPixmap(":/src/image/head3.png"), "Karl");
	createOneFriend(2, QPixmap(":/src/image/head4.png"), "Macy");
	createOneFriend(3, QPixmap(":/src/image/head5.png"), "Tanya");
	createOneFriend(4, QPixmap(":/src/image/head6.png"), "Terry");
	createOneFriend(5, QPixmap(":/src/image/head7.png"), "Able");
	createOneFriend(6, QPixmap(":/src/image/head8.png"), "Jocelyn");
	sortFriends();
	addAllFriends();
}

void ContactForm::createOneFriend(int i, QPixmap img, QString name)
{
	formList[i]->initial(img, name, "");
}

void ContactForm::addAllFriends()
{
	QChar divide = ' ';
	for (int i = 0; i < 7; i++) {
		//出现新字母
		if (divide != formList[i]->getName().at(0).toUpper()) {
			divide = formList[i]->getName().at(0).toUpper();
			QListWidgetItem *header = nullptr;

			QWidget *w = new QWidget();
			Ui::CharHeadForm *charForm = new Ui::CharHeadForm();
			charForm->setupUi(w);

			charForm->labelCharHead->setText(QString(" ").append(divide));
			header = new QListWidgetItem(ui->friendList);
			header->setSizeHint(QSize(ui->friendList->width(), 35));
			ui->friendList->addItem(header);
			ui->friendList->setItemWidget(header, charForm->labelCharHead);
		}
		//    layout->add
		QListWidgetItem *aitem = new QListWidgetItem(ui->friendList);
		aitem->setSizeHint(QSize(ui->friendList->width(), 50));
		ui->friendList->addItem(aitem);
		ui->friendList->setItemWidget(aitem, formList[i]);

	}
}
void ContactForm::sortFriends()
{
	//按字典序比较并排序
	int i, j;
	PerPersonForm *temp = nullptr;
	for (i = 1; i < 7; i++) {
		temp = formList[i];
		j = i - 1;
		while ((j >= 0) && formList[j]->getName() > temp->getName()) {
			formList[j + 1] = formList[j];
			j--;
		}
		if (j != i - 1)
			formList[j + 1] = temp;
	}
}

ContactForm::~ContactForm()
{
	delete ui;
}
