#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QString>
class JsonObject
{
public:
    JsonObject();
    JsonObject(int command, int value);
    void setValuesVolume(QString target, QString control, float value);
    void setValuesEQ(QString target, QString control, float low, float mid, float high);
    void setValuesPlay(QString target, QString control, float value);
    QString target;
    QString control;
    QString value;
    QJsonObject object
    {
        {"target", ""},
        {"control", ""},
        {"value", 0}
    };
    QJsonObject eq_object
    {
        {"low", 0},
        {"mid", 0},
        {"high", 0}
    };
};

#endif // JSONOBJECT_H
