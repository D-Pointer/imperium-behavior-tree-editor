#include <QDebug>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QStandardPaths>
#include <QInputDialog>

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

    // tree widget signals
    connect( ui->tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(editNode()) );

    // add the actions to the window so that shortcuts work
    addAction( ui->m_newNodeAction );
    addAction( ui->m_deleteNodeAction );
    addAction( ui->m_includeSubtreeAction );
    addAction( ui->m_editNodeAction );

    // create the popup menu
    connect( ui->m_newNodeAction, &QAction::triggered, this, &MainWindow::newNode );
    connect( ui->m_deleteNodeAction, &QAction::triggered, this, &MainWindow::deleteNode );
    connect( ui->m_editNodeAction, &QAction::triggered, this, &MainWindow::editNode );
    connect( ui->m_includeSubtreeAction, &QAction::triggered, this, &MainWindow::includeSubtree );

    // create the root
    m_root = new Node( nodeData[kSequence], ui->tree );
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent * event) {
    if ( isWindowModified() ) {
        if ( QMessageBox::question( this, "Confirm", "You have unsaved changes,\nreally quit?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No ) {
            event->ignore();
            return;
        }
    }

    event->accept();
}


void MainWindow::newTree () {
    if ( isWindowModified() ) {
        if ( QMessageBox::question( this, "Confirm", "You have unsaved changes,\nreally create a new tree?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No ) {
            return;
        }
    }

    ui->tree->clear();
    m_root = new Node( nodeData[kSequence], ui->tree );
    setWindowModified( false );
}


void MainWindow::openTree () {
    if ( isWindowModified() ) {
        if ( QMessageBox::question( this, "Confirm", "You have unsaved changes,\nreally open a tree?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No ) {
            return;
        }
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
        m_root = new Node( nodeData[kSequence], ui->tree );
    }
    else {
        ui->tree->addTopLevelItem( m_root );
    }

    ui->tree->expandAll();
    setWindowModified( false );
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
    else {
        setWindowModified( false );
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
    if ( isWindowModified() ) {
        if ( QMessageBox::question( this, "Confirm", "You have unsaved changes,\nreally quit?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No ) {
            return;
        }
    }

    close();
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
        popup.addAction( ui->m_includeSubtreeAction );
    }

    // root can not be deleted
    if ( ! node->isRoot() ) {
        popup.addAction( ui->m_editNodeAction );
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
        node->setComment( dialog.getComment() );
        node->setup();

        // an if-node?
        if ( node->getType() == kIf ) {
            // prepopulate it
            new Node( nodeData[kCanAssault], "", node );
            new Node( nodeData[kSequence], "", node );
            new Node( nodeData[kSequence], "", node );
        }

        node->setExpanded( true );
        item->setExpanded( true );

        setWindowModified( true );
    }
}


void MainWindow::deleteNode () {
    Node * node = dynamic_cast<Node *>( ui->tree->currentItem() );
    if ( ! node ) {
        qDebug() << "MainWindow::deleteNode: no current item";
        return;
    }

    // don't delete the root
    if ( node->isRoot() ) {
        return;
    }

    if ( QMessageBox::question( this, "Confirm", QString("Really delete the '%1' node?").arg(node->getTypeText()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
        delete node;
        setWindowModified( true );
    }
}


void MainWindow::editNode () {
    Node * node = dynamic_cast<Node *>( ui->tree->currentItem() );
    if ( ! node ) {
        qDebug() << "MainWindow::editNode: no current item";
        return;
    }

    NewNodeDialog dialog( node );
    if ( dialog.exec() == QDialog::Accepted ) {
        node->setup();

        // make sure that leaves do not have children
        if ( node->childCount() > node->getMaxChildCount() ) {
            QMessageBox::warning(this, "Warning", "This node now has too many children!\nRemoving the extra child nodes.");
            while ( node->childCount() > node->getMaxChildCount() ) {
                node->removeChild( node->child( node->childCount() - 1 ) );
            }
        }

        // an if-node?
        if ( node->getType() == kIf && node->childCount() < node->getMaxChildCount() ) {
            // need a first condition?
            if ( node->childCount() == 0 ) {
                new Node( nodeData[kCanAssault], "", node );
            }

            // add in sequence nodes for the rest
            while ( node->childCount() < node->getMaxChildCount() ) {
                new Node( nodeData[kSequence], "", node );
            }
        }

        node->setExpanded( true );
        setWindowModified( true );
    }
}


void MainWindow::includeSubtree () {
    QTreeWidgetItem * parent = ui->tree->currentItem();
    if ( ! parent ) {
        qDebug() << "MainWindow::includeSubtree: no current item";
        return;
    }

    bool ok;
    QString filename = QInputDialog::getText(this, "Include Subtree",
                                         "Subree filename:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !filename.isEmpty()) {
        Node * node = new Node( nodeData[kIncludeSubtree], filename, parent );
        parent->setExpanded( true );
        setWindowModified( true );
    }
}
