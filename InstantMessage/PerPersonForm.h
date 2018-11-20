#ifndef PERPERSONFORM_H
#define PERPERSONFORM_H

#include <QWidget>

namespace Ui {
class PerPersonForm;
}

class PerPersonForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PerPersonForm(QWidget *parent = nullptr);
    ~PerPersonForm();
    
private:
    Ui::PerPersonForm *ui;
};

#endif // PERPERSONFORM_H
