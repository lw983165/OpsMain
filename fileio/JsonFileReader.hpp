#pragma once

#include "IFileReader.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <QPoint>
#include <QColor>
#include <QSize>

class Circle;
class Shape;
class Line;
class Text;
class Gauge;

namespace kylink {
class Rectangle;
}

class Svg;

class JsonFileReader : public IFileReader
{
public:
    JsonFileReader();
    virtual ~JsonFileReader();

    void setup(Group *mainGroup) override;
    bool read(const std::string &fileDir) override;

    static QPoint readPoint(const QJsonObject &p);
    static QColor readColor(const QJsonObject &c);

protected:
    virtual void readGroup(Group *group, const QJsonArray &groupObj);
    virtual Circle *readCircle(const QJsonObject &c);
    virtual kylink::Rectangle *readRectangle(const QJsonObject &r);
    virtual Line *readLine(const QJsonObject &l);
    virtual Svg *readSvg(const QJsonObject &l);
    virtual Text *readText(const QJsonObject &l);
    virtual Gauge* readGauge(const QJsonObject &l);
    virtual void readShape(Shape *s, const QJsonObject &obj);

    Group *m_mainGroup;
};

