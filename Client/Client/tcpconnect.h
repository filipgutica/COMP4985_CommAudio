#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QDialog>

namespace Ui {
class TcpConnect;
}

class TcpConnect : public QDialog
{
    Q_OBJECT

public:
    explicit TcpConnect(QWidget *parent = 0);
    ~TcpConnect();

private:
    Ui::TcpConnect *ui;
};

#endif // TCPCONNECT_H
