#include "application.h"
#include "ui_application.h"
#include "configure.h"


Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
}

Application::~Application()
{
    delete ui;
}

//btn click listener
void Application::on_pushButton_clicked()
{
    QString fName;

    fName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                tr("All files (*.*);;mp3 File (*.mp3);;wav File (*.wav)")
                );

   ui->playList->addItem(fName);

}

void Application::on_actionConfigure_triggered()
{
    QString port;   // Port number from the edittext
    int portnum;    // integer to put the port number
    Configure conf;

    conf.setModal(true); // Open the configure dialog

    if (conf.exec() == QDialog::Accepted)
    {
        port = conf.getPort();

        portnum = atoi(port.toUtf8().constData());

        StartServer(portnum, (LPVOID)this);  // VOID pointers hallelujah

    }

}

void Application::appendToLog(QString str)
{
    emit valueChanged(str);
}
