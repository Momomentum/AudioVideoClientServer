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
#include "customdata.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CustomData *data, QWidget *parent = 0);
    ~MainWindow();
//    Ui::MainWindow *getMainWindow();
    float music_cross;
    float music_master;
    float music_left_master;
    float music_left_high;
    float music_left_mid;
    float music_left_low;
    float music_left_effect_1;
    float music_left_effect_2;
    float music_left_effect_3;
    float music_right_master;
    float music_right_high;
    float music_right_mid;
    float music_right_low;
    float music_right_effect_1;
    float music_right_effect_2;
    float music_right_effect_3;
    float video_left_red;
    float video_left_green;
    float video_left_blue;
    float video_right_red;
    float video_right_green;
    float video_right_blue;
    float video_cross;
    bool playing_left = false;
    bool playing_right = false;

    CustomData *data;

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

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
