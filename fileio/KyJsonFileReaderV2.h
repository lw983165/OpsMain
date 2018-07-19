#ifndef KYJSONFILEREADERV2_H
#define KYJSONFILEREADERV2_H

#include "HtJsonFileReader.h"

#include <QMap>

namespace v2 {

class KyJsonFileReader : public HtJsonFileReader
{
public:
    KyJsonFileReader();

protected:
    virtual void translate(const QJsonObject& src, QJsonObject& dest);

private:
    QMap<QString, QString> symbols;
};

}


#endif // KYJSONFILEREADERV2_H
