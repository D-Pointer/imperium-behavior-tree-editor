
#include <QDebug>
#include <QObject>

#include "NewNodeDialog.hpp"
#include "ui_NewNodeDialog.h"

NewNodeDialog::NewNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNodeDialog) {
    ui->setupUi(this);

    categoryChanged( ui->category->currentIndex() );
    typeChanged( ui->type->currentIndex() );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(categoryChanged(int)) );
    connect( ui->type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)) );
}


NewNodeDialog::~NewNodeDialog() {
    delete ui;
}


NodeData NewNodeDialog::getNodedata () const {
    return nodeData[ ui->type->currentData().toInt() ];
}


int NewNodeDialog::getValue () const {
    return ui->value->value();
}


void NewNodeDialog::categoryChanged (int category) {
    ui->type->clear();

    for ( unsigned int index = 0; index < kUnusedMax - 1; ++index ) {
        NodeData & data( nodeData[ index] );
        if ( data.m_category == category ) {
            ui->type->addItem( data.m_typeText, data.m_type );
        }
    }
}


void NewNodeDialog::typeChanged (int index) {
    NodeData & data( nodeData[ ui->type->currentData().toInt()] );

    ui->value->setEnabled( data.m_hasValue );
    ui->value->setValue( data.m_value );
}
