#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>
#include <QTimer>




MainWindow::MainWindow(CustomData *data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->data = data;
    ui->setupUi(this);
    QPixmap libraryPix("Assets/library.jpg");
    QIcon libraryIcon = libraryPix;
    QPixmap streamPix("Assets/stream.jpg");
    QIcon streamIcon = streamPix;
    QPixmap musicMixPix("Assets/audiomix.jpg");
    QIcon musicMixIcon = musicMixPix;
    QPixmap videoMixPix("Assets/videomix.jpg");
    QIcon videoMixIcon = videoMixPix;
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_7->setIcon(libraryIcon);
    ui->pushButton_7->setIconSize(QSize(192,108));
    ui->pushButton_8->setIcon(streamIcon);
    ui->pushButton_8->setIconSize(QSize(192,108));
    ui->pushButton_9->setIcon(musicMixIcon);
    ui->pushButton_9->setIconSize(QSize(192,108));
    ui->pushButton_10->setIcon(videoMixIcon);
    ui->pushButton_10->setIconSize(QSize(192,108));


    // TCP SOCKET
    socket = new QTcpSocket();

}

MainWindow::~MainWindow()
{

    socket->close();
    gst_element_set_state (data->video1_pipeline, GST_STATE_NULL);
    gst_object_unref (data->video1_pipeline);

    gst_element_set_state (data->left_audio_pipeline, GST_STATE_NULL);
    gst_object_unref(data->left_audio_pipeline);
    gst_element_set_state (data->right_audio_pipeline, GST_STATE_NULL);
    gst_object_unref(data->right_audio_pipeline);
//    process->terminate();
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
//    player->play();
//    player->setVolume(50);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
//    player->setVolume(0);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_9_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
//    player->setVolume(0);
}

void MainWindow::on_dial_valueChanged(int value)
{
    music_left_high = float(value)/10;
    commandsObject.setValuesEQ("audio_1","eq",music_left_low,music_left_mid,music_left_high);

    QJsonDocument *doc = new QJsonDocument(commandsObject.object);

    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    QString json = doc->toJson(doc->JsonFormat::Compact);
    socket->write(json.toUtf8(), json.size());
    socket->waitForBytesWritten();

    delete(doc);
    //QJsonDocument sendDocument = new QJsonDocument(object);
    //qDebug << sendDocument.toJson("Indented");
}

void MainWindow::on_dial_2_valueChanged(int value)
{
    music_left_mid = float(value)/10;
    commandsObject.setValuesEQ("audio_1","eq",music_left_low,music_left_mid,music_left_high);

    QJsonDocument *doc = new QJsonDocument(commandsObject.object);

    socket->connectToHost(serveradress, 2345);
    QString json = doc->toJson(doc->JsonFormat::Compact);
    qDebug() << json;
    socket->waitForConnected();
    socket->write(json.toUtf8(), json.size());
    socket->waitForBytesWritten();
}

void MainWindow::on_dial_3_valueChanged(int value)
{
    music_left_low = float(value)/10;
    commandsObject.setValuesEQ("audio_1","eq",music_left_low,music_left_mid,music_left_high);

    QJsonDocument *doc = new QJsonDocument(commandsObject.object);

    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    QString json = doc->toJson(doc->JsonFormat::Compact);
    socket->write(json.toUtf8(), json.size());
    socket->waitForBytesWritten();
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
    music_left_master = (float)value/100;
    commandsObject.setValuesVolume("audio_1","volume",music_left_master);

    QJsonDocument *doc = new QJsonDocument(commandsObject.object);

    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    QString json = doc->toJson(doc->JsonFormat::Compact);
    socket->write(json.toUtf8(), json.size());
    qDebug() << json.size();
    socket->waitForBytesWritten();

    delete(doc);

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
    music_right_master = (float)value/100;
    commandsObject.setValuesVolume("audio_2","volume",music_right_master);

    QJsonDocument *doc = new QJsonDocument(commandsObject.object);

    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    QString json = doc->toJson(doc->JsonFormat::Compact);
    socket->write(json.toUtf8(), json.size());
    qDebug() << json.size();
    socket->waitForBytesWritten();

    delete(doc);
}

void MainWindow::on_pushButton_12_clicked()
{
    serveradress = ui->lineEdit->text();



   socket->connectToHost(serveradress, 2345);
   socket->waitForConnected();
   socket->write("init",5);

   data->left_audio_pipeline = gst_pipeline_new("audio_pipeline");
   data->left_audio_src = gst_element_factory_make("udpsrc", "udp_audio_src");
   data->left_audio_depay = gst_element_factory_make("rtpL16depay", "audio_depay");
   data->left_audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");



   GstCaps *audio_caps = gst_caps_new_simple(
       "application/x-rtp",
       "media", G_TYPE_STRING, "audio",
       "clock-rate", G_TYPE_INT, 48000,
       "encoding-name", G_TYPE_STRING, "L16",
       "encoding-params", G_TYPE_STRING, "2",
       "channels", G_TYPE_INT, 2,
       "payload", G_TYPE_INT, 96,
       NULL
   );


   g_object_set(G_OBJECT(data->left_audio_src), "port", 3001, NULL);
   g_object_set(G_OBJECT(data->left_audio_src), "caps", audio_caps, NULL);

   //g_object_set(data->left_audio_src, "uri", "file:///home/moritzmg/Music/output.wav");

   //gst_caps_unref(audio_caps);

   if (data->left_audio_sink == NULL) {
       g_error ("Couldn't find a working audio sink.");
   }


   // Link audio pipeline
   gst_bin_add_many (GST_BIN (data->left_audio_pipeline), data->left_audio_src, data->left_audio_depay, data->left_audio_sink, NULL);

//   gst_bin_add_many (GST_BIN (data->left_audio_pipeline), data->left_audio_src, NULL);


   gst_element_link(data->left_audio_src, data->left_audio_depay);
   gst_element_link(data->left_audio_depay, data->left_audio_sink);



   /* run the pipeline */
    GstStateChangeReturn sret = gst_element_set_state (data->left_audio_pipeline, GST_STATE_PLAYING);

   if (sret == GST_STATE_CHANGE_FAILURE /*|| audioret == GST_STATE_CHANGE_FAILURE*/) {

       qDebug() << "CRASH!!!!";

        gst_element_set_state (data->left_audio_pipeline, GST_STATE_NULL);
        gst_object_unref (data->left_audio_pipeline);
       /* Exit application */
       QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
   }

   data->right_audio_pipeline = gst_pipeline_new("audio_pipeline");
   data->right_audio_src = gst_element_factory_make("udpsrc", "udp_audio_src");
   data->right_audio_depay = gst_element_factory_make("rtpL16depay", "audio_depay");
   data->right_audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");



//   GstCaps *audio_caps = gst_caps_new_simple(
//       "application/x-rtp",
//       "media", G_TYPE_STRING, "audio",
//       "clock-rate", G_TYPE_INT, 48000,
//       "encoding-name", G_TYPE_STRING, "L16",
//       "encoding-params", G_TYPE_STRING, "2",
//       "channels", G_TYPE_INT, 2,
//       "payload", G_TYPE_INT, 96,
//       NULL
//   );


   g_object_set(G_OBJECT(data->right_audio_src), "port", 3002, NULL);
   g_object_set(G_OBJECT(data->right_audio_src), "caps", audio_caps, NULL);

   //g_object_set(data->right_audio_src, "uri", "file:///home/moritzmg/Music/output.wav");

   gst_caps_unref(audio_caps);

   if (data->right_audio_sink == NULL) {
       g_error ("Couldn't find a working audio sink.");
   }


   // Link audio pipeline
   gst_bin_add_many (GST_BIN (data->right_audio_pipeline), data->right_audio_src, data->right_audio_depay, data->right_audio_sink, NULL);

//   gst_bin_add_many (GST_BIN (data->right_audio_pipeline), data->right_audio_src, NULL);


   gst_element_link(data->right_audio_src, data->right_audio_depay);
   gst_element_link(data->right_audio_depay, data->right_audio_sink);



   /* run the pipeline */
    GstStateChangeReturn sret2 = gst_element_set_state (data->right_audio_pipeline, GST_STATE_PLAYING);

   if (sret2 == GST_STATE_CHANGE_FAILURE /*|| audioret == GST_STATE_CHANGE_FAILURE*/) {

       qDebug() << "CRASH!!!!";

        gst_element_set_state (data->right_audio_pipeline, GST_STATE_NULL);
        gst_object_unref (data->right_audio_pipeline);
       /* Exit application */
       QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
   }

//       data->video1_pipeline = gst_pipeline_new("xoverlay");
//       data->video1_src = gst_element_factory_make("udpsrc", "src");
//       data->video1_depay = gst_element_factory_make("rtph264depay", "depay");
//       data->video1_dec = gst_element_factory_make("avdec_h264", "videodec");
//       data->video1_sink = gst_element_factory_make("xvimagesink", "x_sink");

//       GstCaps *caps = gst_caps_new_simple(
//           "application/x-rtp",
//           "media", G_TYPE_STRING, "video",
//           "clock-rate", G_TYPE_INT, 90000,
//           "encoding-name", G_TYPE_STRING, "H264",
//           "payload", G_TYPE_INT, 96,
//           NULL
//       );


//       g_object_set(G_OBJECT(data->video1_src), "port", 3000, NULL);
//       g_object_set(G_OBJECT(data->video1_src), "caps", caps, NULL);

//       gst_caps_unref(caps);

//       // Link video pipeline
//       gst_bin_add_many (GST_BIN (data->video1_pipeline), data->video1_src, data->video1_depay, data->video1_dec, data->video1_sink, NULL);

//       gst_element_link(data->video1_src, data->video1_depay);
//       gst_element_link(data->video1_depay, data->video1_dec);
//       gst_element_link(data->video1_dec, data->video1_sink);

//       QWidget *widget = this->findChild<QWidget*>("widget");
//          Q_ASSERT(widget);
//          WId xwinid = widget->winId();
//          gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data->video1_sink), xwinid);

//          /* run the pipeline */

//          GstStateChangeReturn sret3 = gst_element_set_state (data->video1_pipeline, GST_STATE_PAUSED);

//          if (sret3 == GST_STATE_CHANGE_FAILURE /*|| audioret == GST_STATE_CHANGE_FAILURE*/) {

//              gst_element_set_state (data->video1_pipeline, GST_STATE_NULL);
//              gst_object_unref (data->video1_pipeline);

//              qDebug() << "CRASH!!!!";

//              /* Exit application */
//              QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
//          }
}

void MainWindow::on_dial_17_valueChanged(int value)
{
    video_left_red = value;
}

void MainWindow::on_dial_14_valueChanged(int value)
{
    video_left_green = value;
}

void MainWindow::on_dial_18_valueChanged(int value)
{
    video_left_blue = value;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    video_cross = value;
}

void MainWindow::on_dial_20_valueChanged(int value)
{
    video_right_red = value;
}

void MainWindow::on_dial_15_valueChanged(int value)
{
    video_right_green = value;
}

void MainWindow::on_dial_19_valueChanged(int value)
{
    video_right_blue = value;
}

void MainWindow::on_pushButton_15_clicked()
{
    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    if(!playing_left)
    {
        playing_left = true;
        commandsObject.setValuesPlay("audio_1","play",1);

        QJsonDocument *doc = new QJsonDocument(commandsObject.object);


        QString json = doc->toJson(doc->JsonFormat::Compact);
        socket->write(json.toUtf8(), json.size());
        socket->waitForBytesWritten();

        delete(doc);
    } else
    {
        playing_left = false;
        commandsObject.setValuesPlay("audio_1","play",0);

        QJsonDocument *doc = new QJsonDocument(commandsObject.object);


        QString json = doc->toJson(doc->JsonFormat::Compact);
        socket->write(json.toUtf8(), json.size());
        socket->waitForBytesWritten();
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    socket->connectToHost(serveradress, 2345);
    socket->waitForConnected();
    if(!playing_right)
    {
        playing_right = true;
        commandsObject.setValuesPlay("audio_2","play",1);

        QJsonDocument *doc = new QJsonDocument(commandsObject.object);


        QString json = doc->toJson(doc->JsonFormat::Compact);
        socket->write(json.toUtf8(), json.size());
        socket->waitForBytesWritten();

        delete(doc);
    } else
    {
        playing_right = false;
        commandsObject.setValuesPlay("audio_2","play",0);

        QJsonDocument *doc = new QJsonDocument(commandsObject.object);


        QString json = doc->toJson(doc->JsonFormat::Compact);
        socket->write(json.toUtf8(), json.size());
        socket->waitForBytesWritten();
    }
}
