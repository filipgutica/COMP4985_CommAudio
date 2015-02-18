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

//btn click listener
void Application::on_pushButton_clicked()
{
    ui->pushButton->setText("Clicked!");
}
