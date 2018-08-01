#include "QGauge.h"

#include <QtWidgets>

QGauge::QGauge(QWidget *parent) : QWidget(parent)
{
    background = QString(":/file/icons/fan_bg.svg");
    pointer = QString(":/file/icons/fan_pointer.svg");
}
void QGauge::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    if (value < minValue) value = minValue;
//    else if (value > maxValue) value = maxValue;


    //绘制背景图
    QImage img2(pointer);
    if (!img2.isNull()) {
        img2 = img2.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawImage(0, 0, img2);
//        painter.rotate(0);
    }
    QImage img(background);
    if (!img.isNull()) {
        img = img.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawImage(0, 0, img);
    }
}
