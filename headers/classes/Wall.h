#include "Static_Object.h"
#pragma once



class Wall : public Static_Object
{
    public:
        Wall(int s, float x, float y, string i);
        
        sf::RectangleShape render() override;
};