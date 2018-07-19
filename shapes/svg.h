#ifndef SVG_H
#define SVG_H

#include "Shape.hpp"
#include "IImage.h"

#include <QtSvg/QtSvg>


class Svg : public Shape, public IImage
{
public:
    Svg();

    /// IDraw
    virtual void draw(QPainter *painter);
    virtual QRect getBoundary();
    virtual bool contains(int x, int y);

    /// Image
    virtual QSize getSize() const;
    virtual void setSize(QSize &val);

    virtual QString getImagePath() const;
    virtual void setImagePath(QString &val);

protected:
    void setSizeByImage();

protected:
    QString imagePath;
    QSvgRenderer svgRender;
    QRect boundary;
    QSize size;
};

#endif // SVG_H
