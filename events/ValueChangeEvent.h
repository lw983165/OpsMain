#ifndef VALUECHANGEEVENT_H
#define VALUECHANGEEVENT_H

#include "EventDef.h"


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
