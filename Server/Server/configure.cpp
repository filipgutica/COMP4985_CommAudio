/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		configure.cpp -   Source file for the start/configure server dialog class
--
--	PROGRAM:			Server.exe
--
--	FUNCTIONS:			Configure
--						~Configure
--						on_buttonBox_accepted()
--						on_buttonBox_rejected()
--						getPort()
--
--	DATE:				Febuary 19 2015
--
--	DESIGNERS:			Filip Gutica & Auto-generated
--
--	PROGRAMMERS:		Filip Gutica & Auto-generated
--
--	NOTES:
--	Instantiates a dialog class for getting the port on which the server will listen.
---------------------------------------------------------------------------------------*/
#include "configure.h"
#include "ui_configure.h"

/*------------------------------------------------------------------------------
--	FUNCTION: Configure()
--
--	PURPOSE:		Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
Configure::Configure(QWidget *parent) : QDialog(parent), ui(new Ui::Configure)
{
    ui->setupUi(this);
}

/*------------------------------------------------------------------------------
--	FUNCTION: ~Configure()
--
--	PURPOSE:		Destructor, cleans up the ui. Deletes the ui object
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
Configure::~Configure()
{
    delete ui;
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_buttonBox_accepted()
--
--	PURPOSE:		gets the port from the QLineEdit widget when user hits "ok"
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void Configure::on_buttonBox_accepted()
{
    QString port = ui->lineEdit->text();
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_buttonBox_rejected()
--
--	PURPOSE:		returns when user hits cancel
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void Configure::on_buttonBox_rejected()
{
    return;
}

/*------------------------------------------------------------------------------
--	FUNCTION: getPort()
--
--	PURPOSE:		getter for getting the port the user entered.
--
--	PARAMETERS:
--		void
--
--  RETURN:
--      QString     user inputted port number
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
QString Configure::getPort()
{
    return ui->lineEdit->text();
}
