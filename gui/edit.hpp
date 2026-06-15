#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "config.hpp"
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
        text.setCharacterSize(FontSizes::INPUT);
        text.setFillColor(Colors::INPUT_TEXT);
    }

    void setPosition(float x, float y) override
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

    bool handleEvent(const sf::Event& event) override
    {
        if (!visible || disabled) return false;

        bool handled = false;

        if (auto* mouse = event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePos = {static_cast<float>(mouse->position.x),
                                     static_cast<float>(mouse->position.y)};

            if (text.getGlobalBounds().contains(mousePos))
            {
                focused = true;
                handled = true;
            }
            else
            {
                focused = false;
            }
        }
        if (focused && event.is<sf::Event::TextEntered>())
        {
            auto* t = event.getIf<sf::Event::TextEntered>();

            if (t->unicode == '\b' && !input.empty())
            {
                input.pop_back();
                handled = true;
            }
            else if (t->unicode == '\r')
            {
                focused = false;
                handled = true;
            }
            else if ((t->unicode >= '0' && t->unicode <= '9') || t->unicode == '-')
            {
                std::string newChar;
                newChar += static_cast<char>(t->unicode);
                std::string newInput = input + newChar;

                bool ok = true;

                if (newInput.length() > 5)
                {
                    ok = false;
                }

                if (t->unicode == '-' && input.length() > 0)
                {
                    ok = false;
                }

                if (ok && newInput != "-")
                {
                    int val = std::stoi(newInput);
                    if (val < -999 || val > 9999)
                    {
                        ok = false;
                    }
                }

                if (ok)
                {
                    input = newInput;
                    handled = true;
                }
            }
        }

        return handled;
    }
};