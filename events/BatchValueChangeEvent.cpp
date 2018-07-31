#include "BatchValueChangeEvent.h"

static const QEvent::Type EvBatchValueChange = (QEvent::Type)QEvent::registerEventType(EV_BATCH_VALUE_CHANGE);

BatchValueChangeEvent::BatchValueChangeEvent()
    : QInputEvent(Type(EvBatchValueChange))
{

}

BatchValueChangeEvent::~BatchValueChangeEvent()
{
    release();
}

int BatchValueChangeEvent::size() const
{
    return values.size();
}

UiValue *BatchValueChangeEvent::get(size_t index)
{
    if (index < values.size()) return values[index];
    else return nullptr;
}

void BatchValueChangeEvent::add(UiValue *val)
{
    values.push_back(val);
}

std::vector<UiValue *> BatchValueChangeEvent::all()
{
    return values;
}

void BatchValueChangeEvent::release()
{
    for (size_t i = 0; i < values.size(); i++)
        delete values[i];
    values.clear();
}

void BatchValueChangeEvent::attach(std::vector<UiValue *> &arr)
{
    values.insert(values.end(), arr.begin(), arr.end());
}

std::vector<UiValue *> BatchValueChangeEvent::detatch()
{
    std::vector<UiValue *> ret = values;
    values.clear();
    return ret;
}
