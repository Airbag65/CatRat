#include "../headers/includes/common.h"
#pragma once

class State
{
public:
    State() = default;
    virtual ~State() = default;

    sf::RenderWindow window{sf::VideoMode(1600, 1000), "CatRat"};

    virtual void print() = 0;
    virtual void run() = 0;

protected:
    sf::Font font;
    
    sf::Text set_text(string, unsigned int, float);
};
