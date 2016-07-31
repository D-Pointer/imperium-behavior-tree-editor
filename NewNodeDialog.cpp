
#include <QDebug>
#include <QObject>

#include "NewNodeDialog.hpp"
#include "ui_NewNodeDialog.h"

NewNodeDialog::NewNodeDialog(Node * node, QWidget *parent) : QDialog(parent), ui(new Ui::NewNodeDialog), m_node(node) {
    ui->setupUi(this);

    if ( m_node ) {
        ui->category->setCurrentIndex( node->getCategory() );

        // update the node when we're done
        connect( ui->buttonBox, &QDialogButtonBox::accepted, this, &NewNodeDialog::updateNode );
    }

    categoryChanged( ui->category->currentIndex() );

    if ( m_node ) {
        for ( int index = 0; index < ui->type->count(); ++index ) {
            if ( ui->type->itemData( index ).toInt() == node->getType() ) {
                ui->type->setCurrentIndex( index );
                break;
            }
        }
    }

    typeChanged( ui->type->currentIndex() );

    // finally set the value as typeChanged() above sets it to 0
    if ( m_node ) {
        ui->value->setText( node->getValue() );
    }

    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(categoryChanged(int)) );
    connect( ui->type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)) );
}


NewNodeDialog::~NewNodeDialog() {
    delete ui;
}


NodeData NewNodeDialog::getNodedata () const {
    return nodeData[ ui->type->currentData().toInt() ];
}


QString NewNodeDialog::getValue () const {
    return ui->value->text();
}


void NewNodeDialog::categoryChanged (int category) {
    ui->type->clear();

    for ( unsigned int index = 0; index < kUnusedMax; ++index ) {
        NodeData & data( nodeData[ index] );
        if ( data.m_category == category ) {
            ui->type->addItem( data.m_typeText, data.m_type );
        }
    }
}


void NewNodeDialog::typeChanged (int index) {
    NodeData & data( nodeData[ ui->type->currentData().toInt()] );

    ui->value->setEnabled( data.m_hasValue );
    ui->value->clear();
}


void NewNodeDialog::updateNode () {
    // precautions
    if ( ! m_node ) {
        return;
    }

    m_node->setNodeData( nodeData[ ui->type->currentData().toInt()] );
    m_node->setValue( ui->value->text() );
}
