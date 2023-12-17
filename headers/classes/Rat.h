#include "../includes/common.h"
#include "Movable_Object.h"
#pragma once



class Rat : public Movable_Object
{
    public:
        ~Rat() = default;
        Rat(int s, float x, float y);
        
        void change_direction(sf::Event::KeyEvent);
        void take_damage(const int damage);
        void set_end_message(string const& s);
        void kill() { alive = !alive; }
        void fix_coordinates();
        void fix_x();
        void fix_y();
        void update(Time & t) override;
        
        bool is_dead(){return !alive;}
        int get_health() const {return health;}
        int get_cheese() const {return cheese_counter;}
        
        string cause_of_end() const {return end_message;}
        
        sf::RectangleShape render() override;
        
        Vector2f move() override;

    private:
        bool alive; 
        bool can_move(Vector2f const& new_coords) override;
        bool handle_collision(shared_ptr<Object> &) override;

        int health;
        int cheese_counter{};
        int big_size;

        string end_message;
};