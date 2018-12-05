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
	connect(ui->list, SIGNAL(currentRowChanged(int)), this, SLOT(getIdByIndex(int)));
	connect(this, SIGNAL(freshInfoPage(int)), personInfoForm, SLOT(freshInfo(int)));
}


ContactForm::~ContactForm()
{
	delete ui;
}

Ui::SessionForm *ContactForm::getUi() const
{
	return ui;
}

PersonInfoForm *ContactForm::getPersonInfoForm() const
{
	return personInfoForm;
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
	refreshFriends();
}

void ContactForm::getIdByIndex(int currIndex)
{
	//判断选中的item是哪一个user
	int count = -1;
	for (int i = 0; i <= currIndex; i++)
		if (ui->list->item(i)->whatsThis() == "A Friend Of You")
			count++;
	emit freshInfoPage(count);
}

void ContactForm::createOneFriendItem(int userid, QPixmap img, QString name)
{
	ListItemForm *p = new ListItemForm(this, userid, img, name);
	friendFormList.push_back(p);
}

void ContactForm::refreshFriends()
{
	MainSystem *system = MainSystem::getSystem();
	//根据系统信息更新会话列表
	ui->list->clear();
	for (auto iter : system->getFriends()) {
		createOneFriendItem(iter.getIdUser(), *(iter.getHeadImg()), iter.getNameUser());
	}
	addAllFriendsIntoList();
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
			header->setFlags(Qt::ItemFlag::ItemIsSelectable);
			ui->list->addItem(header);
			ui->list->setItemWidget(header, w);
		}
		//    layout->add
		QListWidgetItem *aitem = new QListWidgetItem(ui->list);
		aitem->setWhatsThis("A Friend Of You");
		aitem->setSizeHint(QSize(ui->list->width(), 50));
		ui->list->addItem(aitem);
		ui->list->setItemWidget(aitem, friendFormList.at(i));

	}
}
