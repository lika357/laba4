#pragma once
#include "layout.hpp"
#include "widget.hpp"

class HorizontalLayout : public Layout
{
   private:
    float startX;
    float startY;
    float gap;

   public:
    HorizontalLayout(float x, float y, float spacing = 10) : startX(x), startY(y), gap(spacing)
    {
    }

    Layout& append(Widget& widget) override
    {
        float currentX = startX;

        if (widgets.GetLength() > 0)
        {
            Widget* last = widgets.GetLast();
            currentX = last->getPosition().x + last->getSize().x + gap;
        }

        widget.setPosition(currentX, startY);
        widgets.Append(&widget);
        return *this;
    }

    Layout& prepend(Widget& widget) override
    {
        float shift = widget.getSize().x + gap;
        for (size_t i = 0; i < widgets.GetLength(); i++)
        {
            Widget* w = widgets[i];
            w->setPosition(w->getPosition().x + shift, startY);
        }
        widget.setPosition(startX, startY);
        Layout::prepend(widget);
        return *this;
    }
};