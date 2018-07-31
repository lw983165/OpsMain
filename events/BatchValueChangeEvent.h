#pragma once

#include "EventDef.h"

#include <vector>

class UiValue
{
public:
    QString ui_id;
    long data_id;
    QString time;
    QString value;
    long value_type;
};

class BatchValueChangeEvent : public QInputEvent
{
public:
    BatchValueChangeEvent();
    virtual ~BatchValueChangeEvent();

    int size() const;

    UiValue* get(size_t index);
    void add(UiValue* val);
    std::vector<UiValue*> all();
    void release();

    void attach(std::vector<UiValue*>& arr);
    std::vector<UiValue*> detatch();

private:
    std::vector<UiValue*> values;
};
