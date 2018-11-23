#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>

namespace Ui
{
class ChatForm;
}

class ChatForm : public QWidget
{
	Q_OBJECT

public:
	explicit ChatForm(QWidget *parent = nullptr);
	void initControl();
	void on_pushButton_14_clicked();
	~ChatForm();

private slots:
	void on_label_linkActivated(const QString &link);

private:
	Ui::ChatForm *ui;
};

#endif // CHATFORM_H
