#include "mainwindow.h"
#include "ui_mainwindow.h"

QProcess *process;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap libraryPix("Assets/audio-video.JPG");
    QIcon libraryIcon = libraryPix;
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_7->setIcon(libraryIcon);
    ui->pushButton_7->setIconSize(QSize(192,108));
    //vidWidget = new QVideoWidget;
    player = new QMediaPlayer;
    resultPlayer = new QMediaPlayer;
    leftPlayer = new QMediaPlayer;
    rightPlayer = new QMediaPlayer;
    player->setVideoOutput(ui->widget);
    resultPlayer->setVideoOutput(ui->widget_2);
    leftPlayer->setVideoOutput(ui->widget_3);
    rightPlayer->setVideoOutput(ui->widget_4);

    process = new QProcess();
    QStringList args = QString("-v udpsrc uri=127.0.0.1 port=3000 ! application/x-rtp,media=audio, clock-rate=22000, width=16, height=16, encoding-name=L16, encoding-params=1, channels=1 ! rtpL16depay ! audioconvert ! autoaudiosink ").split(" ");
    process->start("gst-launch-1.0", args);

    player->setMedia(QUrl("rtsp://192.168.0.15:8554/test"));
    resultPlayer->setMedia(QUrl("rtsp://192.168.0.15:8554/test"));
    leftPlayer->setMedia(QUrl("rtsp://192.168.0.15:8554/audio1"));

    //player->play();

    //qDebug() << player->state();
    //qDebug() << player->mediaStream();
}

MainWindow::~MainWindow()
{
    process->terminate();
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    fileNames.append(QFileDialog::getOpenFileName(this, tr("load Audio"), "/", tr("Audio Files (*.mp3 *.aac *.wav)")));
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(fileNames);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_8_clicked()
{

    ui->stackedWidget->setCurrentIndex(3);
    player->play();
    player->setVolume(50);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    player->setVolume(0);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    resultPlayer->setVolume(0);
    leftPlayer->setVolume(0);
    rightPlayer->setVolume(0);
}

void MainWindow::on_pushButton_9_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    leftPlayer->setVolume(50);
    leftPlayer->play();
    resultPlayer->setVolume(0);
    resultPlayer->play();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    player->setVolume(0);
}

void MainWindow::on_dial_valueChanged(int value)
{
    music_left_high = value;
}

void MainWindow::on_dial_2_valueChanged(int value)
{
    music_left_mid = value;
}

void MainWindow::on_dial_3_valueChanged(int value)
{
    music_left_low = value;
}

void MainWindow::on_dial_4_valueChanged(int value)
{
    music_left_effect_1 = value;
}

void MainWindow::on_dial_5_valueChanged(int value)
{
    music_left_effect_2 = value;
}

void MainWindow::on_dial_6_valueChanged(int value)
{
    music_left_effect_3 = value;
}

void MainWindow::on_dial_13_valueChanged(int value)
{
    music_master = value;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    music_left_master = value;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    music_cross = value;
}

void MainWindow::on_dial_7_valueChanged(int value)
{
    music_right_high = value;
}

void MainWindow::on_dial_10_valueChanged(int value)
{
    music_right_mid = value;
}

void MainWindow::on_dial_11_valueChanged(int value)
{
    music_right_low = value;
}

void MainWindow::on_dial_8_valueChanged(int value)
{
    music_right_effect_1 = value;
}

void MainWindow::on_dial_12_valueChanged(int value)
{
    music_right_effect_2 = value;
}

void MainWindow::on_dial_9_valueChanged(int value)
{
    music_right_effect_3 = value;
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    music_right_master = value;
}

void MainWindow::on_pushButton_12_clicked()
{
    serveradress = ui->lineEdit->text();
    //qDebug() << serveradress;
    player->setMedia(QUrl("rtsp://"+serveradress+":8554/test"));
    resultPlayer->setMedia(QUrl("rtsp://"+serveradress+":8554/test"));
    leftPlayer->setMedia(QUrl("rtsp://"+serveradress+":8554/audio1"));
}
