#include "logindialog.h"
#include "ui_logindialog.h"
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginDialog::loginPushButtonClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loginPushButtonClicked()
{
    QString userName = ui->userNameLineEdit->text();

    if(!userName.isEmpty())
    {
        emit userLoggedIn(userName);
        this->done(QDialog::Accepted);
    }
}
