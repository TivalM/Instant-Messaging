#ifndef INFORMLISTITEMFORM_H
#define INFORMLISTITEMFORM_H

#include <QWidget>

namespace Ui {
class InformListItemForm;
}

class InformListItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit InformListItemForm(QWidget *parent = 0, QPixmap img=QPixmap(":/src/image/toolOne.png"), QString name="", QString content="");
    ~InformListItemForm();

private slots:
    void on_agreeBtn_clicked();

    void on_rejectBtn_clicked();

private:
    Ui::InformListItemForm *ui;
    QPixmap head;
    QString name;
    QString content;
};

#endif // INFORMLISTITEMFORM_H
