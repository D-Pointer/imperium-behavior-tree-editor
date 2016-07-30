#ifndef NEWNODEDIALOG_HPP
#define NEWNODEDIALOG_HPP

#include <QDialog>

#include "NodeTypes.hpp"

namespace Ui {
class NewNodeDialog;
}

class NewNodeDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewNodeDialog(QWidget *parent = 0);
    ~NewNodeDialog();


    NodeData getNodedata () const;
    int getValue () const;


private slots:

    void categoryChanged (int index);
    void typeChanged (int index);


private:
    Ui::NewNodeDialog *ui;
};

#endif // NEWNODEDIALOG_HPP
