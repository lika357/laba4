#pragma once
#include "layout.hpp"

class FreeLayout : public Layout
{
   public:
    Layout& append(Widget& widget) override
    {
        widgets.Append(&widget);
        return *this;
    }
};