#include "gui/lika_window.hpp"

sf::Font Widget::defaultFont;

int main()
{
    LikaWindow lw(1280, 740, "LAZY SEQUENCE TESTER");
    lw.run();
    return 0;
}