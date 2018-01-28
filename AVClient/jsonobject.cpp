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
    this->value = QString::number(value,'f',3);
    this->control = control;
    object.insert("control", this->control);
    object.insert("value", this->value);
    object.insert("target", this->target);
    object.remove("src");
}

void JsonObject::setValuesEQ(QString target, QString control, float low, float mid, float high)
{
    this->target = target;
    this->control = control;
    object.insert("target", this->target);
    object.insert("control", this->control);
    eq_object.insert("low",QString::number(low,'f',3));
    eq_object.insert("mid", QString::number(mid,'f',3));
    eq_object.insert("high",QString::number(high,'f',3));
    object.insert("value", eq_object);
    object.remove("src");

}

void JsonObject::setValuesPlay(QString target, QString control, float value)
{
    this->target = target;
    this->control = control;
    this->value = value;
    object.insert("target",this->target);
    object.insert("control", this->control);
    object.insert("value", QString::number(value,'f',0));
    object.remove("src");
}
