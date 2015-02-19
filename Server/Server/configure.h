#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "server.h"

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

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Configure *ui;
};

#endif // CONFIGURE_H
