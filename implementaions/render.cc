#include "../headers/includes/include.h"
#include "../headers/includes/common.h"

sf::RectangleShape Object::generate_shape(){
    float dim = size;
    
    Vector2f f{dim, dim};
    sf::RectangleShape shape{f};
    
    shape.setPosition(coords);
    return shape;
}

void Movable_Object::get_texture_direction()
{

    switch (direction)
    {
    case 'w':
        texture = up;
        break;
    case 'a':
        texture = left;
        break;
    case 's':
        texture = down;
        break;
    case 'd':
        texture = right;
        break;
    default:
        break;
    }
}

sf::RectangleShape Cat::render()
{
    sf::RectangleShape cat{generate_shape()};
    get_texture_direction();
    cat.setTexture(&texture);

    return cat;
}

sf::RectangleShape Wall::render()
{
    sf::RectangleShape wall{shape};
    if (identity == "Wall")
    {
        wall.setFillColor(sf::Color::Blue);
    } else if (identity == "Floor")
    {
        wall.setFillColor(sf::Color::Transparent);
    }

    return wall;
}

sf::RectangleShape Rat::render()
{
    sf::RectangleShape rat{generate_shape()};
    get_texture_direction();
    rat.setTexture(&texture);
    return rat;
}

sf::RectangleShape Rat_Trap::render()
{
    sf::RectangleShape rat_trap{shape};
    if (!activated)
    {
        rat_trap.setTexture(&texture);
    }
    else
    {
        rat_trap.setTexture(&activated_texture);
    }
    return rat_trap;
}

sf::RectangleShape Cheese::render()
{
    sf::RectangleShape cheese{shape};
    cheese.setTexture(&texture);
    return cheese;
}