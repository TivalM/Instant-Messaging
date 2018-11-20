#ifndef SESSIONFORM_H
#define SESSIONFORM_H

#include <QWidget>

namespace Ui
{
class SessionForm;
}

class SessionForm : public QWidget
{
	Q_OBJECT

public:
	explicit SessionForm(QWidget *parent = nullptr);
	void refreshFriends();
	~SessionForm();

private:
	Ui::SessionForm *ui;
};

#endif // SESSIONFORM_H
