#ifndef KYJSONFILEREADER_H
#define KYJSONFILEREADER_H

#include "HtJsonFileReader.h"

class KyJsonFileReader : public HtJsonFileReader
{
public:
    KyJsonFileReader();

protected:
    virtual void translate(const QJsonObject& src, QJsonObject& dest);
};

#endif // KYJSONFILEREADER_H
