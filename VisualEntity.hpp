#pragma once

#include "ISelectable.hpp"
#include "IDrawable.hpp"
#include "ITransformable.hpp"
#include "common/PropertySupport.h"

#include <QWidget>

class QPainter;
class Group;
class ActiveSelection;



class VisualEntity : public IDrawable, public ISelectable, public ITransformable, public PropertySupport
{
public:
    VisualEntity();
    virtual ~VisualEntity();

    void setSelected(bool val) override;
    void toogleSelect() override;
    bool isSelected() override;

    /// get visual component id
    QString getId() const override;
    void setId(const QString& id);

    /// get data-binding id
    QString getDataId() const;
    void setDataId(const QString& id);

    void setParentGroup(Group *val);
    Group* getParentGroup();
    void selfDestruct();

    int getIndex() const;
    void setIndex(int value);
    ///
    QWidget* binding();
    void binding(QWidget* widget);

protected:
    Group *m_parentGroup;
    ActiveSelection *m_selection;
    QString id;

    QWidget* mBinding;
    int m_index;
};

