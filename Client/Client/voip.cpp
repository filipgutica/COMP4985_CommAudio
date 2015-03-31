#include "voip.h"
#include "ui_voip.h"
#include "configure.h"
#include <QDebug>
Voip::Voip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voip)
{
    ui->setupUi(this);
}

Voip::~Voip()
{
    delete ui;
}

void Voip::on_makeCallBtn_clicked()
{
    Configure conf;
    conf.setModal(true);

    if(conf.exec() == QDialog::Accepted)
    {
        port = conf.getPort();
        ip = conf.getIP();

    }
    qDebug() << "IP" + ip + "\nPORT" + port;
    //ConnectTCP(ip, port);

}
void Voip::on_acceptCallBtn_clicked()
{
    qDebug() << "Call Received";
}
