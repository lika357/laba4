#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "widget.hpp"

class Button : public Widget
{
   private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;

   public:
 Button(const std::string& label) : text(Widget::getDefaultFont())
    {
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color(101, 67, 33));
        text.setString(label);
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::Black);
        shape.setSize({200, 50});
    }
    Button(const std::string& label, 
           float width, 
           float height,
           std::function<void()> callback = nullptr)
        : text(Widget::getDefaultFont())
    {
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color(101, 67, 33));
        text.setString(label);
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::Black);
        shape.setSize({width, height}); 
        Widget::setSize(width, height);
        if (callback){
             onClick = callback;
        }  
    }

    void setPosition(float x, float y) override
    {
        Widget::setPosition(x, y);
        shape.setPosition({x, y});
        sf::FloatRect b = text.getLocalBounds();
        text.setPosition({x + size.x / 2 - b.size.x / 2, y + size.y / 2 - b.size.y / 2 - 5});
    }

    void setOnClick(std::function<void()> callback)
    {
        onClick = callback;
    }

    void draw(sf::RenderWindow& window) override
    {
        if (!visible) return;
        window.draw(shape);
        window.draw(text);
    }
    void setColor(sf::Color fillColor)
    {
        shape.setFillColor(fillColor);
    }

    void handleEvent(const sf::Event& event) override
    {
        if (!visible || disabled) return;
        if (auto* mouse = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (shape.getGlobalBounds().contains(
                    {static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y)}))
            {
                if (onClick) onClick();
            }
        }
    }
};