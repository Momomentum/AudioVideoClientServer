#include "jsonobject.h"

JsonObject::JsonObject()
{

}

JsonObject::JsonObject(int command, int value)
{
    this->control = command;
    this->value = value;
}

void JsonObject::setValuesVolume(QString target, QString control, float value)
{
    this->target = target;
    this->value = value;
    this->control = control;
    object.insert("control", this->control);
    object.insert("value", this->value);
    object.insert("target", this->target);
    object.remove("src");
    qDebug() << object.value("control");
    qDebug() << object.value("value");
    qDebug() << object.value("target");
}

void JsonObject::setValuesEQ(QString target, QString control, float low, float mid, float high)
{
    this->target = target;
    this->control = control;
    object.insert("target", this->target);
    object.insert("control", this->control);
    eq_object.insert("low",low);
    eq_object.insert("mid", mid);
    eq_object.insert("high",high);
    object.insert("value", eq_object);
    object.remove("src");
    qDebug() << object.value("control");
    qDebug() << object.value("value");
    qDebug() << object.value("target");
}
