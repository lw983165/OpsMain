#include "Canvas.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Group.hpp"
#include "ActiveSelection.hpp"
#include "SelectionTool.hpp"
#include "events/EventDef.h"
#include "events/BatchValueChangeEvent.h"
#include "ValueChangeTool.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    m_mainGroup = new Group();
    m_selection = &ActiveSelection::getInstance();

    m_activeTool = nullptr;
    valueChangeTool = new ValueChangeTool(this);

    setBackgroundColor(Qt::white);
}

Canvas::~Canvas()
{
    delete m_mainGroup;
}

VisualEntity *Canvas::getVEFromPosition(int x, int y)
{
    return m_mainGroup->getClicked(x, y);
}

VisualEntity *Canvas::getVEFromId(const QString &id)
{
    for (int i = 0; i < m_mainGroup->getSize(); i++){
        VisualEntity* entity = m_mainGroup->get(i);
        if (!id.compare(entity->getId()))
            return entity;
    }
    return nullptr;
}

void Canvas::setBackgroundColor(QColor val)
{
    QPalette Pal;
    Pal.setColor(QPalette::Background, val);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void Canvas::addVisualEntity(VisualEntity *val)
{
    m_mainGroup->add(val);
}

void Canvas::setActiveTool(Tool *val)
{
    m_activeTool = val;
}

Tool *Canvas::getActiveTool() const
{
    return m_activeTool;
}

Group *Canvas::getMainGroup()
{
    return m_mainGroup;
}

// bear in mind doing this will delete m_mainGroup
void Canvas::setMainGroup(Group *group)
{
    delete m_mainGroup;
    m_mainGroup = group;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    m_mainGroup->draw(painter);
    if (m_selection) m_selection->draw(painter);

    delete painter;
}

bool Canvas::event(QEvent *event)
{
    if (!m_activeTool) return false;

    if (event->type() == QEvent::Paint) {
        QPaintEvent *ke = reinterpret_cast<QPaintEvent *>(event);
        paintEvent(ke);
        return true;
    } else if (event->type() == EV_VALUE_CHANGE) {
        valueChangeTool->handleEvent(event);
        repaint();
        return true;
    } else if (event->type() == EV_BATCH_VALUE_CHANGE) {
        valueChangeTool->handleEvent(event);
        return true;
    }

    qDebug() << "Canvas::event ---- " << event->type() ;

    bool result = m_activeTool->handleEvent(event);

    repaint();

    return result;
}
