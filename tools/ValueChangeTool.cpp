#include "ValueChangeTool.h"

#include "ValueChangeEvent.h"
#include "VisualEntity.hpp"
#include "Canvas.hpp"
#include "ilabel.h"

#include <QDebug>

ValueChangeTool::ValueChangeTool(Canvas *canvas)
 : Tool(canvas)
{
}

bool ValueChangeTool::handleEvent(QEvent *event)
{
    qDebug() << "ValueChangeTool::handleEvent";
    if (event->type() != EV_VALUE_CHANGE) return false;

    ValueChangeEvent* vc = reinterpret_cast<ValueChangeEvent*>(event);
    QString id = vc->shapeId();
    //int type = vc->valueType();

    VisualEntity* entity = m_canvas->getVEFromId(id);
    if (entity) {
        qDebug() << "ValueChangeTool::handleEvent: ---- " << id;
        ILabel* label = dynamic_cast<ILabel*>(entity);
        if (label) label->setText(id);
    }

    qDebug() << "ValueChangeTool::handleEvent end";

    return true;
}
