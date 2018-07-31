#include "Text.h"

#include <QPainter>
#include <QFont>
#include <QRect>

Text::Text()
{
    fontFamily = "default";
    fontSize =  12;
}

void Text::draw(QPainter *painter)
{
    // 设置画笔颜色
    painter->setPen(getFillColor());

    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setFamily(fontFamily);
    font.setPointSize(fontSize);
    painter->setFont(font);

    QRect rect(getPosition(), size);
    // 绘制文本
    painter->drawText(rect, Qt::AlignCenter, txt);
}

QRect Text::getBoundary()
{
    int margin = 4;
    return QRect(getPosition().x() - margin,
                 getPosition().y() - margin,
                 size.width()  + margin*2 + 1,
                 size.height() + margin*2 + 1);
}

bool Text::contains(int x, int y)
{
    return getBoundary().contains(x, y);
}

QSize Text::getSize() const
{
    return size;
}

void Text::setSize(const QSize &size)
{
    this->size = size;
}

int Text::getFontSize() const
{
    return fontSize;
}

void Text::setFontSize(int size)
{
    fontSize = size;
}

QString Text::getFontFamily() const
{
    return fontFamily;
}

void Text::setFontFamily(const QString &val)
{
    fontFamily = val;
}

QString Text::getText() const
{
    return txt;
}

void Text::setText(const QString &val)
{
    txt = val;
}
