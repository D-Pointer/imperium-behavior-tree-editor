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
    explicit NewNodeDialog (Node *node = nullptr, QWidget *parent = nullptr);
    ~NewNodeDialog();


    NodeData getNodedata () const;
    QString getValue () const;


private slots:

    void categoryChanged (int index);
    void typeChanged (int index);

    void updateNode ();


private:
    Ui::NewNodeDialog *ui;

    // the optional edited node
    Node * m_node;
};

#endif // NEWNODEDIALOG_HPP
