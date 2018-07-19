#ifndef TEXT_H
#define TEXT_H

#include "Shape.hpp"
#include "ilabel.h"

class Text : public Shape, public ILabel
{
public:
    Text();

    void draw(QPainter *painter) override;
    QRect getBoundary() override;
    bool contains(int x, int y) override;

    QSize getSize() const;
    void setSize(const QSize& size);

    int getFontSize() const;
    void setFontSize(int size);

    QString getFontFamily() const;
    void setFontFamily(const QString& val);

    QString getText() const override;
    void setText(const QString& val) override;



private:
    QString txt;
    QSize size;
    int fontSize;
    QString fontFamily;
};

#endif // TEXT_H
