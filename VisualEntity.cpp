#include "GlobalDrawProperties.hpp"
#include "VisualEntity.hpp"
#include "Group.hpp"
#include "ActiveSelection.hpp"

#include <exception>
#include <stdexcept>
#include <QPainter>

VisualEntity::VisualEntity() :
    m_parentGroup(nullptr)
{
    m_selection = &ActiveSelection::getInstance();
    mBinding = nullptr;
    m_index = -1;
}

VisualEntity::~VisualEntity()
{
    setSelected(false);
}

void VisualEntity::setSelected(bool val)
{
    if (val) {
        m_selection->add(this);
    } else {
        m_selection->remove(this);
    }
}

void VisualEntity::toogleSelect()
{
    m_selection->toggleSelect(this);
}

bool VisualEntity::isSelected()
{
    return m_selection->isSelected(this);
}

QString VisualEntity::getId() const
{
    return id;
}

void VisualEntity::setId(const QString &id)
{
    this->id = id;
}

void VisualEntity::setParentGroup(Group *val)
{
    m_parentGroup = val;
}

Group *VisualEntity::getParentGroup()
{
    return m_parentGroup;
}

void VisualEntity::selfDestruct()
{
    if (m_parentGroup == nullptr) {
        throw std::runtime_error("Self-destruct only works if Visual Entity is under a parent group!");
    }

    m_parentGroup->destroy(m_index);
}

int VisualEntity::getIndex() const
{
    return m_index;
}

void VisualEntity::setIndex(int value)
{
    m_index = value;
}
QWidget *VisualEntity::binding()
{
    return mBinding;
}

void VisualEntity::binding(QWidget *widget)
{
    mBinding = widget;
}

