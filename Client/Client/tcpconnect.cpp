#include "tcpconnect.h"
#include "ui_tcpconnect.h"

TcpConnect::TcpConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpConnect)
{
    ui->setupUi(this);
}

TcpConnect::~TcpConnect()
{
    delete ui;
}
