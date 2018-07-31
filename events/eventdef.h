#pragma once

#include <QEvent.h>


enum VT { vBool, vChar, vShort, vInt32, vInt64, vFloat, vDouble, vString, vArray, vObject, Undefine = 0xFF };

#define EV_VALUE_CHANGE (QEvent::User + 1)
#define EV_BATCH_VALUE_CHANGE (QEvent::User + 2)
