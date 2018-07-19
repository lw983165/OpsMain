#pragma once

#include "Tool.hpp"

class Canvas;

class ValueChangeTool : public Tool
{
public:
    ValueChangeTool(Canvas *canvas);

    bool handleEvent(QEvent *event) override;
};
