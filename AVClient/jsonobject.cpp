#include "jsonobject.h"

JsonObject::JsonObject()
{

}

JsonObject::JsonObject(int command, int value)
{
    this->command = command;
    this->value = value;
}

void JsonObject::setValues(int command, int value)
{
    this->command = command;
    this->value = value;
    object.insert("command", command);
    object.insert("value", value);
    qDebug() << object.value("command");
    qDebug() << object.value("value");
}
