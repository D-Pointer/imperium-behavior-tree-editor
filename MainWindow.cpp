#include <QDebug>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QStandardPaths>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "NewNodeDialog.hpp"
#include "Serializer.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect( ui->tree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect( ui->m_newTreeAction, &QAction::triggered, this, &MainWindow::newTree );
    connect( ui->m_openTreeAction, &QAction::triggered, this, &MainWindow::openTree );
    connect( ui->m_saveAction, &QAction::triggered, this, &MainWindow::saveTree );
    connect( ui->m_saveAsAction, &QAction::triggered, this, &MainWindow::saveTreeAs );
    connect( ui->m_quitAction, &QAction::triggered, this, &MainWindow::quitEditor );

    // add the actions to the window so that shortcuts work
    addAction( ui->m_newNodeAction );
    addAction( ui->m_deleteNodeAction );

    // create the popup menu
    connect( ui->m_newNodeAction, &QAction::triggered, this, &MainWindow::newNode );
    connect( ui->m_deleteNodeAction, &QAction::triggered, this, &MainWindow::deleteNode );

    // create the root
    m_root = new Node( nodeData[kRootType], ui->tree );
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::newTree () {
    if ( QMessageBox::question( this, "Confirm", "Really create a new tree?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
        ui->tree->clear();
        m_root = new Node( nodeData[kRootType], ui->tree );
    }
}


void MainWindow::openTree () {
    if ( QMessageBox::question( this, "Confirm", "Really open a tree?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No ) {
        return;
    }

    QString filename = QFileDialog::getOpenFileName(this, "Open tree",
                                                    QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first(),
                                                    tr("Behavior Trees (*.bt)") );
    if ( filename == "" ) {
        return;
    }

    // this is now our tree
    m_filename = filename;

    // clear the tree
    ui->tree->clear();
    m_root = Serializer().load( m_filename );
    if ( ! m_root ) {
        // failed...
        ui->tree->clear();
        m_root = new Node( nodeData[kRootType], ui->tree );
    }
    else {
        ui->tree->addTopLevelItem( m_root );
    }

    ui->tree->expandAll();
}


void MainWindow::saveTree () {
    if ( m_filename == "" ) {
        saveTreeAs();
        return;
    }

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    if ( ! Serializer().save( m_root, m_filename ) ) {
        // failed...
    }

    QApplication::restoreOverrideCursor();
}


void MainWindow::saveTreeAs () {
    QString filename = QFileDialog::getSaveFileName( this, "Save tree as",
                                                     QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first(),
                                                     tr("Behavior Trees (*.bt)") );
    if ( filename == "" ) {
        return;
    }

    m_filename = filename;
    saveTree();
}


void MainWindow::quitEditor () {
    if ( QMessageBox::question( this, "Confirm", "Really quit?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
       close();
    }
}


void MainWindow::showContextMenu(const QPoint& pos) {
    Node * node = dynamic_cast<Node *>( ui->tree->itemAt(pos) );
    if ( ! node ) {
        return;
    }

    QMenu popup;

    // we can not add to leaf nodes
    if ( node->isComposite() ) {
        popup.addAction( ui->m_newNodeAction );
    }

    // root can not be deleted
    if ( ! node->isRoot() ) {
        popup.addAction( ui->m_deleteNodeAction );
    }

    popup.exec( QCursor::pos() );
}


void MainWindow::newNode () {
    QTreeWidgetItem * item = ui->tree->currentItem();
    if ( ! item ) {
        qDebug() << "MainWindow::newNode: no current item";
        return;
    }

    NewNodeDialog dialog;
    if ( dialog.exec() == QDialog::Accepted ) {
        NodeData data = dialog.getNodedata();
        Node * node = new Node( data, dialog.getValue(), item);
        item->setExpanded( true );
    }
}


void MainWindow::deleteNode () {
    Node * node = dynamic_cast<Node *>( ui->tree->currentItem() );
    if ( ! node ) {
        qDebug() << "MainWindow::deleteNode: no current item";
        return;
    }

    if ( QMessageBox::question( this, "Confirm", QString("Really delete the '%1' node?").arg(node->getTypeText()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
        delete node;
    }
}
