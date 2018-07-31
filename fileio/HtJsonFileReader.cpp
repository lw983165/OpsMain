#include "HtJsonFileReader.h"

#include <stdexcept>
#include <QJsonDocument>
#include <QFile>

#define HT_VER ("6.2.3")

//enum ShapeType { Line = 0, Rectangle, Circle, Svg, Unknown = 0xFF };

void htShape2Line(const QJsonObject& src, QJsonObject& line)
{
    line["Type"] = "Line";
    QJsonObject color;
    QString strColor = src["s"].toObject()["shape.border.color"].toString();
	const char* p = strColor.toStdString().data();
	int r, g, b;
	bool ok;
	color["r"] = r = strColor.mid(1, 2).toInt(&ok, 16);
	color["g"] = g = strColor.mid(3, 2).toInt(&ok, 16);
	color["b"] = b = strColor.mid(5, 2).toInt(&ok, 16);
    line["LineColor"] = color;
    line["LineThickness"] = src["s"].toObject()["shape.border.width"].toInt();
    line["P1"] = src["p"].toObject()["points"].toObject()["__a"].toArray()[0].toObject();
    line["P2"] = src["p"].toObject()["points"].toObject()["__a"].toArray()[1].toObject();
}

void htShape2Circle(const QJsonObject& src, QJsonObject& circle)
{
    ;
}

void htShape2Rectangle(const QJsonObject& src, QJsonObject& rec)
{
    ;
}

int judgeType(const QJsonObject& src)
{
    if (!src.contains("p")) throw std::exception("");
	if (!src.contains("c")) throw std::exception("");
	QString type = src["c"].toString();
    if (src["c"].toString().compare("ht.Shape") == 0)
    {
        if (!src.contains("s")) throw std::exception("");
        if (src["p"].toObject().contains("points")) return IFileReader::LineT;
    } else if (src["c"].toString().compare("ht.Node") == 0)
    {
        if (src["p"].toObject().contains("image")) return IFileReader::SvgT;
    }

    return IFileReader::Unknown;
}

HtJsonFileReader::HtJsonFileReader()
{

}

bool HtJsonFileReader::read(const std::string &fileDir)
{
    QFile loadFile(QString::fromUtf8(fileDir.c_str()));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject htJson = loadDoc.object();
    QJsonObject json;
    translate(htJson, json);
    QJsonArray canvasShapes = json["CanvasShapes"].toArray();

    readGroup(m_mainGroup, canvasShapes);

    return true;
}

void HtJsonFileReader::translate(const QJsonObject &src, QJsonObject &dest)
{
    if (src["v"].toString().compare(QString(HT_VER)))
        throw std::exception("wrong version");

    QJsonArray arr;
    QJsonArray d = src["d"].toArray();
    for (int i = 0; i < d.size(); i++)
    {
        int type = judgeType(d[i].toObject());
        switch (type) {
        case LineT: {
            QJsonObject line;
            htShape2Line(d[i].toObject(), line);
            arr.append(line);
            break;
        }
        case SvgT: {
            arr.append(d[i].toObject());
            break;
        }
        default:
            break;
        }
    }

    dest["CanvasShapes"] = arr;
}
