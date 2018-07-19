#pragma once

#include "ISelectable.hpp"
#include "IDrawable.hpp"
#include "ITransformable.hpp"

class QPainter;
class Group;
class ActiveSelection;

class VisualEntity : public IDrawable, public ISelectable, public ITransformable
{
public:
    VisualEntity();
    virtual ~VisualEntity();

    void setSelected(bool val) override;
    void toogleSelect() override;
    bool isSelected() override;
    QString getId() const override;

    void setId(const QString& id);

    void setParentGroup(Group *val);
    Group* getParentGroup();
    void selfDestruct();

    int getIndex() const;
    void setIndex(int value);

protected:
    Group *m_parentGroup;
    ActiveSelection *m_selection;
    QString id;

    int m_index;
};

