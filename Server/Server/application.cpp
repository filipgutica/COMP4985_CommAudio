#include "application.h"
#include "ui_application.h"
#include "configure.h"

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);

    loadPlayList();
    updatePlaylist();
}

Application::~Application()
{
    delete ui;
}

//btn click listener for add songs
void Application::on_pushButton_clicked()
{
    QString fName;

    fName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                tr("All files (*.*);;mp3 File (*.mp3);;wav File (*.wav)")
                );

    fileList.push_back(fName);

    updatePlaylist();

    //Iterate through std::list
    for (std::list<QString>::iterator iter = fileList.begin(); iter != fileList.end(); ++iter)
    {
        qDebug() << *iter << endl;
    }

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

/***************************************************
 * Load any audio files from the ../Music directory
 * *************************************************/
void Application::loadPlayList()
{
    QDirIterator dirIter("../Music", QDirIterator::Subdirectories);
    QString curFile;

    while (dirIter.hasNext())
    {
        dirIter.next();
        if (QFileInfo(dirIter.filePath()).isFile())
        {
            if (QFileInfo(dirIter.filePath()).suffix() == "mp3"
                    || QFileInfo(dirIter.filePath()).suffix() == "wav")
            {
                curFile = QFileInfo(dirIter.filePath()).fileName();
                qDebug() << curFile;
                fileList.push_back(curFile);
            }
        }
    }
}

void Application::updatePlaylist()
{
    //Add to the list view
    ui->playList->setModel(new QStringListModel(QList<QString>::fromStdList(fileList)));
}
