/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		configure.cpp -   Source file for the client configuration data
--
--	PROGRAM:			Client.exe
--
--	FUNCTIONS:			Configure(QWidget *parent)
--						~Configure()
--						getPort()
--						getIP()
--
--
--	DATE:				March 19 2015
--
--	DESIGNERS:			Auto-Generated
--
--	PROGRAMMERS:		Auto-Generated
--
--	NOTES:
--	This source file contains auto-generated functions by QT which assign callback functions
--  to buttons automatically
---------------------------------------------------------------------------------------*/
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
