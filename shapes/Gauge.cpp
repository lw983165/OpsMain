#include "Gauge.h"

#include <QPainter>
#include <QDebug>
#include <QMatrix>

#define CenterPoint_X  (128 + 50)
#define CenterPoint_Y  (148 + 56)

#define NeedleCenter_X     -50   //
#define NeedleCenter_Y     -56

Gauge::Gauge()
{

}

void Gauge::draw(QPainter *painter)
{
    QString background = QString(":/file/icons/fan_bg.svg");
    QString pointer = QString(":/file/icons/fan_pointer.svg");
    if (!binding()) return;

    if (value < minValue) value = minValue;
    else if (value > maxValue) value = maxValue;

    float angel = ((float)(value - minValue)) / (maxValue - minValue) * 180 - 90.0;
    qDebug() << "minValue: " << minValue
             << ", maxValue: " << maxValue
             << ", value: " << value
             << ", angel: " << angel;
    //绘制背景图
    QImage img(background);
    if (!img.isNull()) {
        img = img.scaled(getSize().width(), getSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawImage(getPosition().x(), getPosition().y(), img);
    } else {
        qDebug() << "background is null";
    }
    //绘制指针
    QImage img2(pointer);
    if (!img2.isNull()) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->translate(CenterPoint_X, CenterPoint_Y);
        painter->rotate(angel);
        img2 = img2.scaled(getSize().width(), getSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawImage(NeedleCenter_X, NeedleCenter_Y, img2);
        painter->restore();
    } else {
        qDebug() << "pointer is null";
    }
}

QRect Gauge::getBoundary()
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

bool Gauge::contains(int x, int y)
{
    return getBoundary().contains(x, y);
}

QSize Gauge::getSize() const
{
    return  size;
}

void Gauge::setSize(QSize &val)
{
    size = val;
}

void Gauge::setMinValue(int val)
{
    minValue = val;
}
void Gauge::setMaxValue(int val)
{
    maxValue = val;
}
void Gauge::setValue(int val)
{
    value = val;
}
