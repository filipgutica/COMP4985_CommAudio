#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QDialog>
#include <QFile>

namespace Ui {
class Downloader;
}

class Downloader : public QDialog
{
    Q_OBJECT

public:
    explicit Downloader(QWidget *parent = 0);
    ~Downloader();
    int SetFileName(QString);
    int SetBytesExpected(int);
    void StartDownload();

private slots:
    void on_CancelButton_clicked();

    void on_OKButton_clicked();

private:
    Ui::Downloader *ui;
    QString filename;
    QFile * file;
    int bytesExpected;
    int bytesReceived;
};

#endif // DOWNLOADER_H
