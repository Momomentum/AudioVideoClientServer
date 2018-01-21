#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
class JsonObject
{
public:
    JsonObject();
    JsonObject(int command, int value);
    void setValues(int command, int value);
    int command;
    int value;
    QJsonObject object
    {
        {"command", 1},
        {"value", 2}
    };
};

#endif // JSONOBJECT_H
