#pragma once
#include <SFML/Graphics.hpp>

#include "../include/list_sequence.hpp"
#include "widget.hpp"

class Layout : public Widget
{
   protected:
    ListSequence<Widget*> widgets;

   public:
    virtual Layout& append(Widget& widget)
    {
        widgets.Append(&widget);
        return *this;
    }
    virtual Layout& prepend(Widget& widget)
    {
        ListSequence<Widget*> temp;
        temp.Append(&widget);
        for (size_t i = 0; i < widgets.GetLength(); i++)
        {
            temp.Append(widgets[i]);
        }
        widgets = temp;
        return *this;
    }

    void removeLast()
    {
        if (widgets.GetLength() == 0) return;

        ListSequence<Widget*> temp;
        for (size_t i = 0; i < widgets.GetLength() - 1; i++)
        {
            temp.Append(widgets[i]);
        }
        widgets = temp;
    }

    void removeFirst()
    {
        widgets.PopFront();
    }

    size_t getWidgetCount() const
    {
        return widgets.GetLength();
    }

    void draw(sf::RenderWindow& window) override
    {
        if (!visible) return;
        for (auto& widget : widgets)
        {
            widget->draw(window);
        }
    }

    bool handleEvent(const sf::Event& event) override
    {
        if (!visible || disabled) return false;

        for (auto& widget : widgets)
        {
            if (widget->handleEvent(event)) return true;
        }

        return false;
    }
};