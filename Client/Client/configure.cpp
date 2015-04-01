#include "configure.h"
#include "ui_configure.h"

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);

    ui->lineEdit_ip->setFocus();
}

Configure::~Configure()
{
    delete ui;
}

QString Configure::getPort()
{
     return ui->lineEdit_port->text();
}

QString Configure::getIP()
{
    return ui->lineEdit_ip->text();
}
