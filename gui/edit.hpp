#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "widget.hpp"

class Edit : public Widget
{
   private:
    sf::Text text;
    std::string input;
    bool focused = false;

   public:
    Edit() : text(Widget::getDefaultFont())
    {
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::Black);
    }

    void setPosition(float x, float y)
    {
        Widget::setPosition(x, y);
        text.setPosition({x, y});
    }

    std::string getInput() const
    {
        return input;
    }

    void clear()
    {
        input = "";
    }

    bool isFocused() const
    {
        return focused;
    }

    void setFocused(bool f)
    {
        focused = f;
    }

    void draw(sf::RenderWindow& window) override
    {
        if (!visible) return;

        std::string display = input;
        if (focused) display += "_";

        text.setString(display);
        window.draw(text);
    }

    void handleEvent(const sf::Event& event) override
    {
        if (!visible || disabled) return;

        if (auto* mouse = event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePos = {static_cast<float>(mouse->position.x),
                                     static_cast<float>(mouse->position.y)};

            if (text.getGlobalBounds().contains(mousePos))
                focused = true;
            else
                focused = false;
        }

        if (focused && event.is<sf::Event::TextEntered>())
        {
            auto* t = event.getIf<sf::Event::TextEntered>();

            if (t->unicode == '\b' && !input.empty())
            {
                input.pop_back();
            }
            else if (t->unicode == '\r')
            {
                focused = false;
            }
            else if ((t->unicode >= '0' && t->unicode <= '9') || t->unicode == '-')
            {
                input += static_cast<char>(t->unicode);
            }
        }
    }
};