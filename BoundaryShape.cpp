#include "BoundaryShape.h"

BoundaryShape::BoundaryShape()
{

}


QRect BoundaryShape::getBoundary()
{
    if (boundary.isEmpty())
    {
        int margin = 4;
        boundary = QRect(getPosition().x() - margin,
                     getPosition().y() - margin,
                     getSize().width()  + margin*2 + 1,
                     getSize().height() + margin*2 + 1);
    }
    return boundary;
}

bool BoundaryShape::contains(int x, int y)
{
    return getBoundary().contains(x, y);
}

QSize BoundaryShape::getSize() const
{
    return  size;
}

void BoundaryShape::setSize(QSize &val)
{
    size = val;
}
