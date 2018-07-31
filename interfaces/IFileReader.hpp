#pragma once

#include <string>

class Group;

class IFileReader
{
public:
    enum ShapeType { LineT = 0, RectangleT, CircleT, Panel, SvgT, TextT, NotSupport = 0xFE, Unknown = 0xFF };

    virtual ~IFileReader() {}

    virtual void setup(Group *mainGroup) = 0;
    virtual bool read(const std::string &fileDir) = 0;
};
