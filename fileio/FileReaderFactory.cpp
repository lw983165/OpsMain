#include "FileReaderFactory.hpp"
#include "JsonFileReader.hpp"
#include "htjsonfilereader.h"
#include "KyJsonFileReader.h"
#include "KyJsonFileReaderV2.h"

#include <QDebug>

IFileReader *FileReaderFactory::create(const std::string &format)
{
    if (format == "json") {
        return new v2::KyJsonFileReader();
    }

    return nullptr;
}
