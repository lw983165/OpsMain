#ifndef HTJSONFILEREADER_H
#define HTJSONFILEREADER_H

#include "JsonFileReader.hpp"

class HtJsonFileReader : public JsonFileReader
{
public:
    HtJsonFileReader();

    virtual bool read(const std::string &fileDir);

protected:
    virtual void translate(const QJsonObject& src, QJsonObject& dest);
};

#endif // HTJSONFILEREADER_H
