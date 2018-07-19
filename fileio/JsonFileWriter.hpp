#pragma once

#include "IFileWriter.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <QPoint>
#include <QColor>

class Circle;
class Shape;
class Line;
namespace kylink {
class Rectangle;
}


class JsonFileWriter : public IFileWriter
{
public:
    JsonFileWriter();
    ~JsonFileWriter();

    void setup(Group *mainGroup) override;
    bool write(const std::string &fileDir) override;


    static QJsonObject writePoint(QPoint p);
    static QJsonObject writeColor(QColor c);

private:
    QJsonArray writeGroup(Group *group);
    QJsonObject writeCircle(Circle *c);
    QJsonObject writeRectangle(kylink::Rectangle *r);
    QJsonObject writeLine(Line *l);
    void writeShape(Shape *s, QJsonObject &obj);

    Group *m_mainGroup;
};

