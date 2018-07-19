#include "KyJsonFileReaderV2.h"

#include <math.h>
#include <QDir>
#include <JsonFileWriter.hpp>

#include "jsondef.h"

namespace v2
{

int judgeKyType(const QJsonObject& src)
{
    if (!src.contains("type")) throw std::exception("");
    QString type = src["type"].toString();
    if (type.compare("scada-line") == 0)
        return IFileReader::LineT;
    else if (type.compare("scada-panel") == 0)
        return IFileReader::RectangleT;
    else if (type.compare("scada-circle") == 0)
        return IFileReader::CircleT;
    else if (type.compare("scada-svg-comp") == 0)
        return IFileReader::SvgT;
    else if (type.compare("scada-label") == 0)
        return IFileReader::TextT;

    return IFileReader::Unknown;
}

void getPositions(const QJsonObject& src, QPoint& topLeft, QSize& size)
{
    int x = src["x"].toInt(), y = src["y"].toInt();
    int w = src["width"].toInt(), h = src["height"].toInt();

    topLeft.setX(x);
    topLeft.setY(y);

    size.setWidth(w);
    size.setHeight(h);
}

void getTopLeftPosition(const QJsonObject& src, QPoint& topLeft, QSize& size)
{
    getPositions(src, topLeft, size);
    topLeft.setX(topLeft.rx() - size.width() / 2);
    topLeft.setY(topLeft.ry() - size.height() / 2);
}

QJsonObject writePoint(int x, int y)
{
    QJsonObject pos;
    pos["x"] = x;
    pos["y"] = y;
    return pos;
}

QJsonObject readKyColor(const QJsonObject& src, QString key)
{
    QJsonObject color;
    QString strColor = src[key].toString();
    int r, g, b;
    bool ok;
    color["r"] = r = strColor.mid(1, 2).toInt(&ok, 16);
    color["g"] = g = strColor.mid(3, 2).toInt(&ok, 16);
    color["b"] = b = strColor.mid(5, 2).toInt(&ok, 16);
    return color;
}

void kyShape2Line(const QJsonObject& src, QJsonObject& line)
{
    line["Type"] = "Line";
    line["id"] =  src["id"].toString();
    QJsonObject color;
    QString strColor = src["params"].toObject()["stroke"].toString();
    int r, g, b;
    bool ok;
    color["r"] = r = strColor.mid(1, 2).toInt(&ok, 16);
    color["g"] = g = strColor.mid(3, 2).toInt(&ok, 16);
    color["b"] = b = strColor.mid(5, 2).toInt(&ok, 16);
    //
    int x0 = src["layout"].toObject()["x"].toInt();
    int y0 = src["layout"].toObject()["y"].toInt();
    int w = src["layout"].toObject()["width"].toInt();
    int h = src["layout"].toObject()["height"].toInt();


    line["LineColor"] = color;
    line["LineThickness"] = src["params"].toObject()["strokeWidth"].toInt();
    line["P1"] = writePoint(x0, y0);
    line["P2"] = writePoint(x0 + w, y0 + h);
}

void kyShape2Circle(const QJsonObject& src, QJsonObject& circle)
{
    circle["Type"] = "Circle";
    circle["id"] =  src["id"].toString();
    QPoint pos;
    QSize size;
    getTopLeftPosition(src["layout"].toObject(), pos, size);
    circle["Position"] = JsonFileWriter::writePoint(pos);
    circle["Radius"] = size.width() / 2;

    circle["LineThickness"] = src["params"].toObject()["strokeWidth"].toInt();
    circle["LineColor"] = readKyColor(src["params"].toObject(), "stroke");
    circle["FillColor"] = readKyColor(src["params"].toObject(), "background");
}

void kyShape2Text(const QJsonObject& src, QJsonObject& txt)
{
    txt[TYPE] = "Text";
    txt["id"] =  src["id"].toString();
    QPoint pos;
    QSize size;
    getTopLeftPosition(src["layout"].toObject(), pos, size);
    txt[POSITION] = JsonFileWriter::writePoint(pos);
	txt[WIDTH] = size.width();
	txt[HEIGHT] = size.height();
    txt[FILLCOLOR] = readKyColor(src["params"].toObject(), "fill");
    txt[TEXT_TEXT] = src["value"].toObject()["val1"].toString();
    txt[TEXT_FONTSIZE] = src["params"].toObject()["fontSize"].toInt();
	txt[TEXT_FONTFAMILY] = src["params"].toObject()["fontFamily"].toString();
}

void kyShape2Rectangle(const QJsonObject& src, QJsonObject& rec)
{
    rec["Type"] = "Rectangle";
    rec["id"] =  src["id"].toString();
    QPoint pos;
    QSize size;
    getPositions(src["layout"].toObject(), pos, size);
    rec["Position"] = JsonFileWriter::writePoint(pos);
    rec["Width"] = size.width();
    rec["Height"] = size.height();

    rec["LineThickness"] = src["params"].toObject()["strokeWidth"].toInt();
    rec["LineColor"] = readKyColor(src["params"].toObject(), "stroke");
    rec["FillColor"] = readKyColor(src["params"].toObject(), "background");
}

int urldecode(char *str, int len)
{
    char *dest = str;
    char *data = str;

    int value;
    int c;

    while (len--) {
        if (*data == '+') {
            *dest = ' ';
        }
        else if (*data == '%' && len >= 2 && isxdigit((int)*(data + 1))
            && isxdigit((int)*(data + 2)))
        {

            c = ((unsigned char *)(data + 1))[0];
            if (isupper(c))
                c = tolower(c);
            value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
            c = ((unsigned char *)(data + 1))[1];
            if (isupper(c))
                c = tolower(c);
            value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

            *dest = (char)value;
            data += 2;
            len -= 2;
        }
        else {
            *dest = *data;
        }
        data++;
        dest++;
    }
    *dest = '/0';
    return dest - str;
}

int urldecode(const QString& src, QString& dest)
{
    std::string str = src.toStdString();
    int len = urldecode(&str[0], str.size());
    if (len > 0) dest = QString::fromStdString(str.substr(0, len));
    return len;
}

void kyShape2Svg(const QJsonObject& src, QJsonObject& svg)
{
    svg["Type"] = "Svg";
    svg["id"] =  src["id"].toString();
    QPoint pos;
    QSize size;
    getTopLeftPosition(src["layout"].toObject(), pos, size);

//    QString img(QDir::currentPath()), decode;
//    img.append(src["src"].toString());
//    urldecode(img, decode);
    svg["image"] = src["name"].toString();
    svg["Position"] = writePoint(pos.rx(), pos.ry());
    svg["width"] = (int)size.width();
    svg["height"] = (int)size.height();
}

void parseSymbols(const QJsonArray &src, QMap<QString, QString>& map)
{
    for (int i = 0; i < src.size(); i++)
    {
        map.insert(src[i].toObject()["id"].toString(), src[i].toObject()["url"].toString());
    }
}


KyJsonFileReader::KyJsonFileReader()
{

}

void KyJsonFileReader::translate(const QJsonObject &src, QJsonObject &dest)
{
    parseSymbols(src["compSymbols"].toArray(), symbols);
    QJsonArray arr;
    QJsonArray d = src["componentList"].toArray();
    for (int i = 0; i < d.size(); i++)
    {
        int type = ::v2::judgeKyType(d[i].toObject());
        switch (type) {
        case LineT: {
            QJsonObject line;
            kyShape2Line(d[i].toObject(), line);
            arr.append(line);
            break;
        } case RectangleT: {
            QJsonObject rec;
            kyShape2Rectangle(d[i].toObject(), rec);
            arr.append(rec);
            break;
        } case CircleT: {
            QJsonObject circle;
            kyShape2Circle(d[i].toObject(), circle);
            arr.append(circle);
            break;
        } case SvgT: {
            QJsonObject svg;
            kyShape2Svg(d[i].toObject(), svg);
			QString id = svg["image"].toString();
            if (!symbols.contains(id)) throw std::exception();
            QString img(QDir::currentPath()), decode;
            img.append(symbols[id]);
            urldecode(img, decode);
            svg["image"] = decode;
            arr.append(svg);
            break;
        } case TextT: {
            QJsonObject txt;
            kyShape2Text(d[i].toObject(), txt);
            arr.append(txt);
            break;
        }
        default:
            break;
        }
    }

    dest["CanvasShapes"] = arr;
}

} /// namespace v2
