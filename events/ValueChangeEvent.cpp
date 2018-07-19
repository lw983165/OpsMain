#include "ValueChangeEvent.h"

static const QEvent::Type EvValueChange = (QEvent::Type)QEvent::registerEventType(EV_VALUE_CHANGE);

ValueChangeEvent::ValueChangeEvent()
 : QInputEvent(Type(EvValueChange))
{
    id = "";
    type = Undefine;
}

QString ValueChangeEvent::shapeId() const
{
    return this->id;
}

void ValueChangeEvent::shapeId(const QString &id)
{
    this->id = id;
}

int ValueChangeEvent::valueType() const
{
    return this->type;
}

void ValueChangeEvent::valueType(int type)
{
    this->type = type;
}
