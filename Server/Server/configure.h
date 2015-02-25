/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	configure.h -		Header file for configure.cpp ui class
--                                      Contains function headers.
--
--	PROGRAM:		Server
--
--
--	DATE:			February 15, 2015
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:		Filip Gutica & Auto-generated
--
--	PROGRAMMER:		Filip Gutica & Auto-generated
--
--	NOTES:
--
---------------------------------------------------------------------------------------*/
#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>


using namespace std;

namespace Ui {
class Configure;
}

class Configure : public QDialog
{
    Q_OBJECT

public:
    explicit Configure(QWidget *parent = 0);
    ~Configure();
    QString getPort();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Configure *ui;
};

#endif // CONFIGURE_H
