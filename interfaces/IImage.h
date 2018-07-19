#ifndef IIMAGE_H
#define IIMAGE_H

#include <QSize>

class IImage
{
public:
    virtual QSize getSize() const = 0;
    virtual void setSize(QSize &val) = 0;

    virtual QString getImagePath() const = 0;
    virtual void setImagePath(QString &val) = 0;

    virtual ~IImage() {}
};

#endif // IIMAGE_H
