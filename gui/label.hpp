#pragma once
#include <SFML/Graphics.hpp>

#include "widget.hpp"

class Label : public Widget
{
   private:
    sf::Text text;

   public:
    Label(const std::string& str) : text(Widget::getDefaultFont())
    {
        text.setString(str);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
    }

    void setPosition(float x, float y)
    {
        Widget::setPosition(x, y);
        text.setPosition({x, y});
    }

    void setText(const std::string& str)
    {
        text.setString(str);
    }

    void draw(sf::RenderWindow& window) override
    {
        if (!visible) return;
        window.draw(text);
    }

    void handleEvent(const sf::Event& event) override
    {
    }
};