#include "JsonFileReader.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include "Shape.hpp"
#include "Group.hpp"
#include "svg.h"
#include "Text.h"
#include "Gauge.h"
#include "LevelBar.h"
#include "jsondef.h"

#include <stdexcept>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

JsonFileReader::JsonFileReader()
{
    m_mainGroup = nullptr;
}

JsonFileReader::~JsonFileReader()
{

}

void JsonFileReader::setup(Group *mainGroup)
{
    m_mainGroup = mainGroup;
}

bool JsonFileReader::read(const std::string &fileDir)
{
    QFile loadFile(QString::fromUtf8(fileDir.c_str()));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject jsonObj = loadDoc.object();
    QJsonArray canvasShapes = jsonObj["CanvasShapes"].toArray();
    readGroup(m_mainGroup, canvasShapes);
    return true;
}

void JsonFileReader::readGroup(Group *group, const QJsonArray &groupObj)
{
    for (int i = 0; i < groupObj.size(); i++) {
        QJsonObject obj = groupObj[i].toObject();
        VisualEntity * child = nullptr;
        if (obj["Type"].toString() == "Circle") {
            child = readCircle(obj);
        } else if (obj["Type"].toString() == "Rectangle") {
            child = readRectangle(obj);
        } else if (obj["Type"].toString() == "Line") {
            child = readLine(obj);
        } else if (obj["Type"].toString() == "Svg") {
            child = readSvg(obj);
        } else if (obj["Type"].toString() == "Text") {
            child = readText(obj);
        } else if (obj["Type"].toString() == "Gauge") {
            child = readGauge(obj);
		} else if (obj["Type"].toString() == "LevelBar") {
			child = readLevelBar(obj);
		} else {
            //throw std::runtime_error("Invalid visual entity!");
        }
		if (child) {
			child->binding(group->binding());
			group->add(child);
		}

        
    }
}

Circle *JsonFileReader::readCircle(const QJsonObject &c)
{
    Circle *circle = new Circle();
    readShape(circle, c);

    circle->setRadius(c["Radius"].toInt());
    circle->setId(c["id"].toString());

    return circle;
}

Text *JsonFileReader::readText(const QJsonObject &c)
{
    Text *txt = new Text();
    txt->setPosition(readPoint(c[POSITION].toObject()));
    txt->setFillColor(readColor(c[FILLCOLOR].toObject()));
    txt->setSize(QSize(c[WIDTH].toInt(), c[HEIGHT].toInt()));
    txt->setFontSize(c[TEXT_FONTSIZE].toInt());
    txt->setFontFamily(c[TEXT_FONTFAMILY].toString());
    txt->setText(c[TEXT_TEXT].toString());
    txt->setId(c["id"].toString());
    return txt;
}

Gauge *JsonFileReader::readGauge(const QJsonObject &json)
{
    qDebug() << "JsonFileReader::readGauge";
    Gauge* gauge = new Gauge();
    gauge->setId(json[ID].toString());
    QJsonObject layout = json[LAYOUT].toObject();
    gauge->setPosition(readPoint(layout));
    gauge->setSize(readSize(layout));
    gauge->setMinValue(json[PARAMS].toObject()[GAUGE_MINVALUE].toString().toInt());
    gauge->setMaxValue(json[PARAMS].toObject()[GAUGE_MAXVALUE].toString().toInt());
    gauge->setValue(json[VALUE].toObject()[GAUGE_VALUE].toInt());
    return gauge;
}

LevelBar *JsonFileReader::readLevelBar(const QJsonObject &json)
{
    LevelBar* bar = new LevelBar();
    bar->setId(json[ID].toString());
    QJsonObject layout = json[LAYOUT].toObject();
    bar->setPosition(readPoint(layout));
    bar->setSize(readSize(layout));
    bar->setBackColor(readColor(json["BackColor"].toObject()));
    bar->setFillColor(readColor(json["FillColor"].toObject()));
    bar->setValue(json["value"].toObject()["val1"].toInt());
    return bar;
}

kylink::Rectangle *JsonFileReader::readRectangle(const QJsonObject &r)
{
    kylink::Rectangle *rect = new kylink::Rectangle();
    readShape(rect, r);
    rect->setId(r["id"].toString());
    rect->setWidth(r["Width"].toInt());
    rect->setHeight(r["Height"].toInt());

    return rect;
}

Line *JsonFileReader::readLine(const QJsonObject &l)
{
    Line *line = new Line();
    line->setId(l["id"].toString());

    line->setP1(readPoint(l["P1"].toObject()));
    line->setP2(readPoint(l["P2"].toObject()));
    line->setLineThickness(l["LineThickness"].toInt());
    line->setLineColor(readColor(l["LineColor"].toObject()));

    return line;
}

Svg *JsonFileReader::readSvg(const QJsonObject &obj)
{
    Svg *svg = new Svg();
    svg->setId(obj["id"].toString());
    svg->setImagePath(obj["image"].toString());
    svg->setPosition(readPoint(obj["Position"].toObject()));
    int w = 0, h = 0;
    if (obj.contains("width")) {
        w = obj["width"].toInt();
        h = obj["height"].toInt();
    }
    svg->setSize(QSize(w, h));

    return svg;
}

void JsonFileReader::readShape(Shape *s, const QJsonObject &obj)
{
    s->setPosition(readPoint(obj["Position"].toObject()));
    s->setFillColor(readColor(obj["FillColor"].toObject()));
    s->setLineColor(readColor(obj["LineColor"].toObject()));
    s->setLineThickness(obj["LineThickness"].toInt());
}

QPoint JsonFileReader::readPoint(const QJsonObject &p)
{
    QPoint point(p["x"].toInt(),
                 p["y"].toInt());

    return point;
}

QColor JsonFileReader::readColor(const QJsonObject &c)
{
    QColor color(c["r"].toInt(),
                 c["g"].toInt(),
                 c["b"].toInt());

    return color;
}

QSize JsonFileReader::readSize(const QJsonObject &c)
{
    QSize size(c["width"].toInt(), c["height"].toInt());
    return size;
}

