#include "Movable_Object.h"
#include "Rat.h"

#pragma once

class Cat : public Movable_Object
{
public:
    ~Cat() = default;
    Cat(int s, float x, float y);

    void update(Time & t) override;
    void set_prey(shared_ptr<Rat> const& r);

    sf::RectangleShape render() override;

private:
    bool rat_is_dead();
    bool can_move(Vector2f const&) override;
    bool handle_collision(shared_ptr<Object> &) override;

    void killing_time();
    void find_player();

    Vector2i delta_coords();
    Vector2f move() override;
    
    shared_ptr<Rat> prey{};
};