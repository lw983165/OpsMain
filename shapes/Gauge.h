#pragma once

#include "Shape.hpp"
#include "widgets/QGauge.h"

#include <QtSvg/QtSvg>
#include <QSize>
#include <QRect>


class Gauge : public Shape
{
public:
    Gauge();
    /// IDraw
    virtual void draw(QPainter *painter);
    virtual QRect getBoundary();
    virtual bool contains(int x, int y);
    ///
    virtual QSize getSize() const;
    virtual void setSize(QSize &val);

    void setMinValue(int val);
    void setMaxValue(int val);
    void setValue(int val);

private:
    QSize size;
    QRect boundary;
    int value, minValue, maxValue;
    QSvgRenderer svgRender;
//    QGauge widget;
};
