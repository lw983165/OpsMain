#include "KyJsonFileReader.h"

#include <math.h>
#include <JsonFileWriter.hpp>


int judgeKyType(const QJsonObject& src)
{
    if (!src.contains("selfType")) throw std::exception("");
    QString type = src["selfType"].toString();
    if (type.compare("line") == 0)
        return IFileReader::LineT;
    else if (type.compare("rect") == 0)
        return IFileReader::RectangleT;
    else if (type.compare("circle") == 0)
        return IFileReader::CircleT;
    else if (type.compare("picture") == 0)
        return IFileReader::SvgT;

    return IFileReader::Unknown;
}

void getPositions(const QJsonObject& src, QPoint& topLeft, QSize& size)
{
    double x = src["left"].toDouble(), y = src["top"].toDouble();
    double scaleX = src["scaleX"].toDouble(), scaleY = src["scaleY"].toDouble();
    double w = src["width"].toDouble() * scaleX, h = src["height"].toDouble() * scaleY;

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
    QJsonObject color;
    QString strColor = src["stroke"].toString();
    int r, g, b;
    bool ok;
    color["r"] = r = strColor.mid(1, 2).toInt(&ok, 16);
    color["g"] = g = strColor.mid(3, 2).toInt(&ok, 16);
    color["b"] = b = strColor.mid(5, 2).toInt(&ok, 16);
    //
    double angle = src["angle"].toDouble();//(src["angle"].toInt() % 90) +  - src["angle"].toInt();
	float x0 = src["left"].toDouble();
	float y0 = src["top"].toDouble();
	double scaleX = src["scaleX"].toDouble();
    double scaleY = src["scaleY"].toDouble();

	double w = scaleX * src["width"].toInt();

	double pi = 3.1415926;

	float sinVal = std::sin(angle * pi / 180);
	float cosVal = std::cos(angle * pi / 180);

	int x1 = x0 - w / 2 * cosVal, x2 = x0 + w / 2 * cosVal;
	int y1 = y0 - w / 2 * sinVal, y2 = y0 + w / 2 * sinVal;

    line["LineColor"] = color;
    line["LineThickness"] = (int)(scaleY * src["strokeWidth"].toInt());
    line["P1"] = writePoint(x1, y1);
    line["P2"] = writePoint(x2, y2);
}

void kyShape2Circle(const QJsonObject& src, QJsonObject& circle)
{
    circle["Type"] = "Circle";
    QPoint pos;
    QSize size;
    getPositions(src, pos, size);
    circle["Position"] = JsonFileWriter::writePoint(pos);
    circle["Radius"] = size.width() / 2;

    circle["LineThickness"] = src["strokeWidth"].toInt();
	circle["LineColor"] = JsonFileWriter::writeColor(QColor(255, 255, 255));
    circle["FillColor"] = readKyColor(src, "fill");
}

void kyShape2Rectangle(const QJsonObject& src, QJsonObject& rec)
{
    rec["Type"] = "Rectangle";
    QPoint pos;
    QSize size;
	getTopLeftPosition(src, pos, size);
    rec["Position"] = JsonFileWriter::writePoint(pos);
    rec["Width"] = size.width();
    rec["Height"] = size.height();

    rec["LineThickness"] = src["strokeWidth"].toInt();
    rec["LineColor"] = JsonFileWriter::writeColor(QColor(255, 255, 255));
    rec["FillColor"] = readKyColor(src, "fill");
}

/**
* @param str 需要解码的url字符串
* @param len 需要解码的url的长度
* @return int 返回解码后的url长度
*/
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
	QString img("C:/work/"), decode;
	img.append(src["src"].toString());
	urldecode(img, decode);
	svg["image"] = decode;
	double x = src["left"].toDouble(), y = src["top"].toDouble();
	double scaleX = src["scaleX"].toDouble(), scaleY = src["scaleY"].toDouble();
	double w = src["width"].toDouble() * scaleX, h = src["height"].toDouble() * scaleY;
    svg["Position"] = writePoint(x - w / 2, y - h / 2);
    svg["width"] = (int)w;
    svg["height"] = (int)h;
}

KyJsonFileReader::KyJsonFileReader()
{

}

void KyJsonFileReader::translate(const QJsonObject &src, QJsonObject &dest)
{
    QJsonArray arr;
    QJsonArray d = src["objects"].toArray();
    for (int i = 0; i < d.size(); i++)
    {
        int type = judgeKyType(d[i].toObject());
        switch (type) {
        case LineT: {
            QJsonObject line;
            kyShape2Line(d[i].toObject(), line);
            arr.append(line);
            break;
		}
		case RectangleT: {
			QJsonObject rec;
			kyShape2Rectangle(d[i].toObject(), rec);
			arr.append(rec);
			break;
		}
		case CircleT: {
			QJsonObject circle;
			kyShape2Circle(d[i].toObject(), circle);
			arr.append(circle);
			break;
		}
        case SvgT: {
            QJsonObject svg;
            kyShape2Svg(d[i].toObject(), svg);
            arr.append(svg);
            break;
        }
        default:
            break;
        }
    }

    dest["CanvasShapes"] = arr;

}
