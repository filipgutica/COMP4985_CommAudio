#include "downloader.h"
#include "ui_downloader.h"

#include <QDebug>

Downloader::Downloader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Downloader)
{
    ui->setupUi(this);
}

Downloader::~Downloader()
{
    delete ui;
}

int Downloader::SetFileName(QString fname)
{
    filename = fname;

    file = new QFile(filename);
    if(!file->open(QFile::WriteOnly))
    {
        qDebug() << "File open failed.";
        return -1;
    }

    return 0;
}

int Downloader::SetBytesExpected(int eb)
{
    if (eb > 0)
    {
        bytesExpected = eb;
        return 0;
    }
    else
    {
        qDebug() << "Not a valid file size.";
        return -1;
    }
}

void Downloader::StartDownload()
{
    // update the progress bar according to bytesReceived / bytesExpected * 100

    // open up socket for listening with timeout of 3 seconds

    // once connected, start downloading from socket and writing to file

    // download complete, close socket and do other stuff


}

void Downloader::on_CancelButton_clicked()
{
    this->reject();
}

void Downloader::on_OKButton_clicked()
{
    this->accept();
}
