#include "logindialog.h"
#include "ui_logindialog.h"
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Logowanie");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
