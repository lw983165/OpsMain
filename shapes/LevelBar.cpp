#include "LevelBar.h"
#include <QPainter>
#include <QRectF>

LevelBar::LevelBar()
{
}

void LevelBar::draw(QPainter *painter)
{
    QBrush brush(getBackColor());
    QPen pen(getLineColor());

    if (getLineThickness() == 0) pen.setStyle(Qt::NoPen);

    pen.setWidth(getLineThickness());

    painter->setBrush(brush);
    painter->setPen(pen);

    /// draw outline rectangle
    painter->drawRect(QRect(getPosition().x(),
                            getPosition().y(),
                            getSize().width(), getSize().height()));
    /// draw inline rectangle
	//painter->setBrush(QBrush(getFillColor()));
	painter->setPen(QPen(Qt::NoPen));
	QRectF rec1(getPosition().x() + (qreal)getLineThickness() / 2, getPosition().y() + getSize().height() - getValue(),
		getSize().width() - getLineThickness(), getValue() - (qreal)getLineThickness() / 2);
	painter->fillRect(rec1, QBrush(getFillColor()));

    // txt position not right
    const QRectF rec(getPosition().x(), getPosition().y(), getSize().width(), 20);
	QString str = QString::number(getValue()) + "%";
	painter->setPen(QPen(getLineColor()));
    painter->drawText(rec, Qt::AlignCenter, str);
}

int LevelBar::getValue() const
{
    return value;
}
void LevelBar::setValue(int val)
{
    this->value = val;
}
QColor LevelBar::getBackColor() const
{
    return backColor;
}
void LevelBar::setBackColor(const QColor &val)
{
    this->backColor = val;
}
