#pragma once

#include "BoundaryShape.h"

class LevelBar : public BoundaryShape
{
public:
    LevelBar();
    /// IDraw
    virtual void draw(QPainter *painter);

    int getValue() const;
    void setValue(int val);
    QColor getBackColor() const;
    void setBackColor(const QColor& val);

private:
    int value;
    QColor backColor;
};

