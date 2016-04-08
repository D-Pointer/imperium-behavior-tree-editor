#include "NewNodeDialog.hpp"
#include "ui_NewNodeDialog.h"

NewNodeDialog::NewNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNodeDialog)
{
    ui->setupUi(this);
}

NewNodeDialog::~NewNodeDialog()
{
    delete ui;
}
