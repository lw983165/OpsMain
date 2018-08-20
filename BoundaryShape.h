#pragma once

#include "Shape.hpp"

#include <QSize>
#include <QRect>

class BoundaryShape : public Shape
{
public:
    BoundaryShape();
    ///
    virtual QRect getBoundary();
    virtual bool contains(int x, int y);
    ///
    virtual QSize getSize() const;
    virtual void setSize(QSize &val);

protected:
    QSize size;
    QRect boundary;
};

