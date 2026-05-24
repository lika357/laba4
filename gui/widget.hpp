#pragma once
#include <SFML/Graphics.hpp>

class Widget
{
   protected:
    bool visible = true;
    bool disabled = false;
    sf::Vector2f position = {0, 0};
    sf::Vector2f size = {200, 50};
    static sf::Font defaultFont;

   public:
    static sf::Font& getDefaultFont()
    {
        return defaultFont;
    }
    virtual ~Widget() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;

    virtual void setPosition(float x, float y)
    {
        position = {x, y};
    }

    sf::Vector2f getPosition() const
    {
        return position;
    }

    virtual void setSize(float w, float h)
    {
        size = {w, h};
    }

    sf::Vector2f getSize() const
    {
        return size;
    }

    void setVisible(bool v)
    {
        visible = v;
    }
    bool isVisible() const
    {
        return visible;
    }
};