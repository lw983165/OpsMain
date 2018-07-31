#pragma once

#include <QString>

class IPropertySupport
{
public:
    virtual ~IPropertySupport() {}

    virtual int   getInt(const QString& key, int def) = 0;
    virtual float getFloat(const QString& key, float def) = 0;
    virtual QString getString(const QString& key, const QString& def) = 0;
};
