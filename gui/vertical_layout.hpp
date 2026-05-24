#pragma once
#include "layout.hpp"

class VerticalLayout : public Layout
{
   private:
    float startX, startY, gap;

   public:
    VerticalLayout(float x, float y, float spacing = 10) : startX(x), startY(y), gap(spacing)
    {
    }

    Layout& append(Widget& widget) override
    {
        float currentY = startY;

        if (widgets.GetLength() > 0)
        {
            Widget* last = widgets.GetLast();
            currentY = last->getPosition().y + last->getSize().y + gap;
        }

        widget.setPosition(startX, currentY);
        widgets.Append(&widget);
        return *this;
    }
    Layout& prepend(Widget& widget) override
    {
        float shift = widget.getSize().y + gap;
        for (size_t i = 0; i < widgets.GetLength(); i++)
        {
            Widget* w = widgets[i];
            w->setPosition(w->getPosition().x, w->getPosition().y + shift);
        }
        widget.setPosition(startX, startY);
        Layout::prepend(widget);
        return *this;
    }
};