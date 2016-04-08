#ifndef NEWNODEDIALOG_HPP
#define NEWNODEDIALOG_HPP

#include <QDialog>

namespace Ui {
class NewNodeDialog;
}

class NewNodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewNodeDialog(QWidget *parent = 0);
    ~NewNodeDialog();

private:
    Ui::NewNodeDialog *ui;
};

#endif // NEWNODEDIALOG_HPP
