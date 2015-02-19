#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QDebug>
#include "server.h"


namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    void appendToLog(QString str);

private slots:
    void on_pushButton_clicked();
    void on_actionConfigure_triggered();

private:
    Ui::Application *ui;

signals:
    void valueChanged(QString);
};

#endif // APPLICATION_H
