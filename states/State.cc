#include "State.h"
#include "../headers/includes/common.h"


sf::Text State::set_text(string text, unsigned int s, float y)
{
    sf::Text t{text, font, s};
    auto bounds{t.getLocalBounds()};
    t.setPosition((window.getSize().x - bounds.width) / 2, y);
    t.setFillColor(sf::Color::White);
    return t;
}