#include "audioplayer.h"
#include "ui_audioplayer.h"

AudioPlayer::AudioPlayer(QWidget *parent) : QDialog(parent), ui(new Ui::AudioPlayer)
{
    ui->setupUi(this);

    player = new QMediaPlayer;

    connect(player, &QMediaPlayer::positionChanged, this, &AudioPlayer::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioPlayer::on_durationChanged);
}

AudioPlayer::~AudioPlayer()
{
    player->stop();
    delete player;
    delete ui;
}

void AudioPlayer::on_btnPlay_clicked()
{
    // ...
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();
}

void AudioPlayer::on_btnPause_clicked()
{
    player->pause();
}

void AudioPlayer::on_btnResume_clicked()
{
    player->play();
}


void AudioPlayer::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void AudioPlayer::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);
}

void AudioPlayer::setAudio(QString file)
{
    filePath = file;
    this->setWindowTitle(filePath);
}

void AudioPlayer::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void AudioPlayer::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}


