#include "Static_Object.h"

#pragma once



class Cheese : public Static_Object
{
    public:
        ~Cheese() = default;
        Cheese(int s, float x, float y);
        
        sf::RectangleShape render() override;
        
};