#include "application.h"
#include "ui_application.h"

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

void Application::on_actionAudio_Stream_triggered()
{

}

void Application::on_actionRadio_triggered()
{
    AudioPlayer audPlayer;

    audPlayer.exec();
}

void Application::on_actionVOIP_triggered()
{

}


