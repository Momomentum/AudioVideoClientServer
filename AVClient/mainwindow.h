#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QJsonDocument>
#include <QProcess>
#include <QTcpSocket>
#include "jsonobject.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    Ui::MainWindow *getMainWindow();
    int music_cross;
    int music_master;
    float music_left_master;
    int music_left_high;
    int music_left_mid;
    int music_left_low;
    int music_left_effect_1;
    int music_left_effect_2;
    int music_left_effect_3;
    int music_right_master;
    int music_right_high;
    int music_right_mid;
    int music_right_low;
    int music_right_effect_1;
    int music_right_effect_2;
    int music_right_effect_3;
    int video_left_red;
    int video_left_green;
    int video_left_blue;
    int video_right_red;
    int video_right_green;
    int video_right_blue;
    int video_cross;
    QString serveradress;
    QStringList fileNames;

    QMediaPlayer* player;
    QMediaPlayer* leftPlayer;
    QMediaPlayer* rightPlayer;
    QMediaPlayer* resultPlayer;
    QTcpSocket* socket;
    JsonObject commandsObject;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_4_clicked();

    void on_dial_valueChanged(int value);

    void on_dial_2_valueChanged(int value);

    void on_dial_3_valueChanged(int value);

    void on_dial_music_left_low_valueChanged(int value);

    void on_dial_4_valueChanged(int value);

    void on_dial_5_valueChanged(int value);

    void on_dial_6_valueChanged(int value);

    void on_dial_13_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_dial_7_valueChanged(int value);

    void on_dial_10_valueChanged(int value);

    void on_dial_11_valueChanged(int value);

    void on_dial_8_valueChanged(int value);

    void on_dial_12_valueChanged(int value);

    void on_dial_9_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_pushButton_12_clicked();

    void on_dial_17_valueChanged(int value);

    void on_dial_14_valueChanged(int value);

    void on_dial_18_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_dial_20_valueChanged(int value);

    void on_dial_15_valueChanged(int value);

    void on_dial_19_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
