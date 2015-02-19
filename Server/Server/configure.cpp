#include "configure.h"
#include "ui_configure.h"

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);
}

Configure::~Configure()
{
    delete ui;
}

void Configure::on_buttonBox_accepted()
{
    QString port = ui->lineEdit->text();

    qDebug() <<  port.toUtf8().constData(); //Convert to regular cstr

    int portnum = atoi(port.toUtf8().constData());

    StartServer(portnum);

}

void Configure::on_buttonBox_rejected()
{
    return;
}
