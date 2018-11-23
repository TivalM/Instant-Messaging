#ifndef TOOLSFORM_H
#define TOOLSFORM_H

#include <QWidget>

namespace Ui {
class ToolsForm;
}

class ToolsForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ToolsForm(QWidget *parent = nullptr);
    ~ToolsForm();
    
private:
    Ui::ToolsForm *ui;
};

#endif // TOOLSFORM_H
