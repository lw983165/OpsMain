#include "PropertySupport.h"

PropertySupport::~PropertySupport()
{
    properties.clear();
}

int PropertySupport::getInt(const QString &key, int def)
{
    if (properties.contains(key))
        return properties[key].toInt();
    else
        return def;
}

float PropertySupport::getFloat(const QString &key, float def)
{
    if (properties.contains(key))
        return properties[key].toFloat();
    else
        return def;
}

QString PropertySupport::getString(const QString &key, const QString &def)
{
    if (properties.contains(key))
        return properties[key].toString();
    else
        return def;
}
