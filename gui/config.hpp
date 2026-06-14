#pragma once

#include <SFML/Graphics.hpp>

namespace Colors
{
const sf::Color BACKGROUND = sf::Color(255, 228, 225);
const sf::Color BUTTON_FILL = sf::Color::White;
const sf::Color BUTTON_OUTLINE = sf::Color(101, 67, 33);
const sf::Color BUTTON_TEXT = sf::Color::Black;
const sf::Color TITLE = sf::Color(101, 67, 33);
const sf::Color INPUT_TEXT = sf::Color::Black;
const sf::Color HINT = sf::Color(120, 70, 70);
const sf::Color RESULT = sf::Color::Black;
const sf::Color ELEMENT = sf::Color(173, 216, 230);
}

namespace Window
{
constexpr float WIDTH = 1200.0f;
constexpr float HEIGHT = 900.0f;
}

namespace ButtonSizes
{
constexpr float CHOOSE_W = 300.0f;
constexpr float CHOOSE_H = 70.0f;

constexpr float STACK_W = 150.0f;
constexpr float STACK_H = 50.0f;

constexpr float ELEMENT_W = 80.0f;
constexpr float ELEMENT_H = 80.0f;
}

namespace FontSizes
{
constexpr unsigned int TITLE = 30;
constexpr unsigned int BUTTON = 22;
constexpr unsigned int INPUT = 28;
constexpr unsigned int RESULT = 24;
constexpr unsigned int HINT = 20;
}

namespace Borders
{
constexpr float BUTTON_THICKNESS = 2.0f;
}

namespace LayoutPositions
{
constexpr float CHOOSE_X = 450.0f;
constexpr float CHOOSE_Y = 250.0f;
constexpr float CHOOSE_GAP = 25.0f;

constexpr float WORK_X = 50.0f;
constexpr float WORK_Y = 80.0f;
constexpr float WORK_GAP = 15.0f;

constexpr float FUNC_Y = 80.0f;
constexpr float FUNC_GAP = 10.0f;

constexpr float ELEM_Y = 150.0f;
constexpr float ELEM_GAP = 10.0f;
}

namespace ElementPositions
{
constexpr float TITLE_X = 450.0f;
constexpr float TITLE_Y = 20.0f;

constexpr float INPUT_X = 50.0f;
constexpr float INPUT_Y = 820.0f;

constexpr float RESULT_X = 50.0f;
constexpr float RESULT_Y = 850.0f;
}