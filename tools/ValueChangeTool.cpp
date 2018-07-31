#include "ValueChangeTool.h"

#include "ValueChangeEvent.h"
#include "BatchValueChangeEvent.h"
#include "VisualEntity.hpp"
#include "Canvas.hpp"
#include "ILabel.h"

#include <QDebug>

ValueChangeTool::ValueChangeTool(Canvas *canvas)
 : Tool(canvas)
{
}

bool ValueChangeTool::handleEvent(QEvent *event)
{
    qDebug() << "ValueChangeTool::handleEvent";
    if (event->type() == EV_VALUE_CHANGE) {
        ValueChangeEvent* vc = reinterpret_cast<ValueChangeEvent*>(event);
        QString id = vc->shapeId();
        int type = vc->valueType();

        VisualEntity* entity = m_canvas->getVEFromId(id);
        if (entity) {
            qDebug() << "ValueChangeTool::handleEvent: ---- " << id;
            ILabel* label = dynamic_cast<ILabel*>(entity);
            if (label) label->setText(id);
        }
    } else if (event->type() == EV_VALUE_CHANGE) {
        BatchValueChangeEvent* bvc = reinterpret_cast<BatchValueChangeEvent*>(event);
        int count = bvc->size();
        qDebug() << "BatchValueChangeTool::handleEvent: ---- " << count;
        for (int i = 0; i < count; i++) {
            UiValue* value = bvc->get(i);
            VisualEntity* entity = m_canvas->getVEFromId(value->ui_id);
            if (!entity) continue;
            ILabel* label = dynamic_cast<ILabel*>(entity);
            if (label) label->setText(value->value);
        }
        bvc->release();
    }
    qDebug() << "ValueChangeTool::handleEvent end";

    return true;
}
