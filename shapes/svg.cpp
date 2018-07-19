#include "svg.h"

Svg::Svg()
{

}

void Svg::draw(QPainter *painter)
{
//    painter->drawImage(boundary, image);
    svgRender.render(painter, QRectF(getPosition(), getSize()));
}

QRect Svg::getBoundary()
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

bool Svg::contains(int x, int y)
{
    return getBoundary().contains(x, y);
}

QSize Svg::getSize() const
{
    return size;
}

void Svg::setSize(QSize &val)
{
    if (val.rwidth() == 0) {
        setSizeByImage();
    } else {
        this->size = val;
    }
}

void Svg::setImagePath(QString &val)
{
    this->imagePath = val;
    svgRender.load(val);
}

void Svg::setSizeByImage()
{

}

QString Svg::getImagePath() const
{
    return imagePath;
}
