#pragma once

#include "IPropertySupport.h"
#include <QVariant>
#include <QMap>

class PropertySupport : public IPropertySupport
{
public:
    virtual ~PropertySupport();

    virtual int   getInt(const QString& key, int def);
    virtual float getFloat(const QString& key, float def);
    virtual QString getString(const QString& key, const QString& def);

protected:
    QMap<QString, QVariant> properties;
};

