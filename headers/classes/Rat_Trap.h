#include "Static_Object.h"
#include "../includes/common.h"
#pragma once


class Rat_Trap : public Static_Object
{
    public:
        ~Rat_Trap() = default;
        Rat_Trap(int s, float x, float y);

        sf::RectangleShape render() override;

        int retrieve_damage() const {return damage;}

        void activate(){activated = true;}

        bool is_activated() {return activated;}

    private:
        const int damage;

        bool activated;

        sf::Texture activated_texture;
};