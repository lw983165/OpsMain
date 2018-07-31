#pragma once

class IDataSource
{
public:
    virtual ~IDataSource() {}

    virtual int init(const char* config) = 0;
    virtual int start() = 0;
    virtual int stop() = 0;

};

