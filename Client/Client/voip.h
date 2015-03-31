#ifndef VOIP_H
#define VOIP_H

#include <QDialog>

namespace Ui {
class Voip;
}

class Voip : public QDialog
{
    Q_OBJECT

public:
    explicit Voip(QWidget *parent = 0);
    ~Voip();

private slots:
    void on_makeCallBtn_clicked();

    void on_acceptCallBtn_clicked();

private:
    Ui::Voip *ui;
    QString ip;
    QString port;
};

#endif // VOIP_H
