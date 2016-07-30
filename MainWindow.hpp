#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMenu>

#include "NodeTypes.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void newTree ();
    void openTree ();
    void saveTree ();
    void saveTreeAs ();
    void quitEditor ();

    void showContextMenu(const QPoint&);
    void newNode ();
    void deleteNode ();


private:
    Ui::MainWindow *ui;

    // tree root
    Node * m_root;

    // current filename
    QString m_filename;
};

#endif // MAINWINDOW_HPP
