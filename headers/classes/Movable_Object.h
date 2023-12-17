#include "Object.h"

#pragma once




class Movable_Object : public Object
{
    public:
        virtual ~Movable_Object() = default;
        Movable_Object(int s, float x, float y, int v, string i);

        virtual void update(Time & t) = 0;
        
    protected:
        const int speed;
         
        
        char direction{'d'};
        char upcoming_direction{direction};

        virtual void get_texture_direction();

        virtual Vector2f move() = 0;

        virtual bool can_move(Vector2f const&) = 0;
        virtual bool handle_collision(shared_ptr<Object> &) = 0;
        
        sf::Texture left;
        sf::Texture right;
        sf::Texture up;
        sf::Texture down;
};