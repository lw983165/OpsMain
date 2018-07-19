#pragma once

#include <QString>

class ILabel
{
public:
    virtual QString getText() const = 0;
    virtual void setText(const QString &txt) = 0;

    virtual ~ILabel() {}
};
