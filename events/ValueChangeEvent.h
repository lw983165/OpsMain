#ifndef VALUECHANGEEVENT_H
#define VALUECHANGEEVENT_H

#include "eventdef.h"


enum VT { vBool, vChar, vShort, vInt32, vInt64, vFloat, vDouble, vString, vArray, vObject, Undefine = 0xFF };

class ValueChangeEvent : public QInputEvent
{
public:
    ValueChangeEvent();

    QString shapeId() const;
    void shapeId(const QString &id);

    int valueType() const;
    void valueType(int type);

private:
    QString id;
    int type;
};

#endif // VALUECHANGEEVENT_H
