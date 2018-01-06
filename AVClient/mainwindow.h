#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int music_cross;
    int music_master;
    int music_left_master;
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
    QStringList fileNames;
    QVideoWidget* vidWidget;
    QMediaPlayer* player;
    QMediaPlayer* leftPlayer;
    QMediaPlayer* rightPlayer;

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
