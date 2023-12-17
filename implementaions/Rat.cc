#include "../headers/includes/common.h"
#include "../headers/classes/Rat.h"
#include "../headers/classes/Rat_Trap.h"
#include "../headers/classes/Cheese.h"

void Rat::take_damage(const int damage)
{
    health -= damage;
    if(health <= 0)
    {
        alive = false;
        end_message = "rat_trap";
    }
}

void Rat::set_end_message(string const& s)
{
    end_message = s;
}

bool Rat::handle_collision(shared_ptr<Object> & o)
{
    string name{o->get_identity()};
    if(name == "Wall")
    {
        // if-satsen nedan fixar så att man inte hamnar för högt upp eller för långt åt vänster när man kolliderar med en vägg
        if(direction == 'w' || direction == 's')
        {
            coords.y += big_size*0.1;
            if(int(coords.y)%big_size > big_size*0.1){
                // kollar så att spelaren inte är för långt ner
                coords.y -= (int(coords.y) % big_size - big_size * 0.1);
            }
            
        }
        else if(direction == 'a' || direction == 'd')
        {
            
                coords.x += big_size*0.1;
            if(int(coords.x) % big_size > big_size * 0.1){
                // kollar så att spelaren inte är för långt till höger
                coords.x -= (int(coords.x) % big_size - big_size * 0.1);
            }
            
        }
        
        /* direction = 'h' ger en temporär riktning (som inte finns med i hanteringen) som gör att spelaren inte rör sig åt något håll när den är intill en vägg.
               ändras så fort spelaren säger att den vill byta riktning */ 
            direction = 'h'; // 'h' för 'hold'
        return false;
    } 
    else if(name == "Cat")
    {
        alive = false;
        end_message = "cat";
        return false;
    } 
    else if(name == "Rat_Trap")
    {
        
        shared_ptr<Rat_Trap> rt{dynamic_pointer_cast<Rat_Trap>(o)};
        
        if(!rt->is_activated())
        {
            
            take_damage(rt->retrieve_damage());
            rt->activate();
        }
        
    }
    else if(name == "Cheese")
    {
        cheese_counter++;
        auto it = std::remove(objects.begin(), objects.end(), o);
        objects.erase(it, objects.end());
    }

    return true;
}


void Rat::fix_x()
{   
    int x{int(coords.x)};
    if(x % big_size > (big_size / 10))
        {
            int diff{(x % big_size) - (big_size / 10)};
            coords.x -= diff; 
        }else if(x % big_size < (big_size / 10))
        {
            int diff{(big_size / 10) - (x % big_size)};
            coords.x += diff; 
        }
}

void Rat::fix_y()
{
    
    int y{int(coords.y)};
    
    if(y % big_size > (big_size / 10))
    {
        int diff{(y % big_size) - (big_size / 10)};
        coords.y -= diff; 
    }else if(y % big_size < (big_size / 10))
    {
        int diff{(big_size / 10) - (y % big_size)};
        coords.y += diff; 
    }
}

void Rat::fix_coordinates()
{
    // Används för att se till att råttan alltid är i mitten av "gången"
    if(direction == 'w' || direction == 's')
    {
        fix_x();
        
    }
    else if(direction == 'a' || direction == 'd')
    {
        fix_y();
    }
}


bool Rat::can_move(Vector2f const& new_coords)
{
    int x{int(new_coords.x)}; 
    x -= (x % big_size); 
    
    
    int y{int(new_coords.y)};
    y -= (y % big_size);

    switch (direction)
    {
    case 's':
        y += big_size;
        break;
    case 'd':
        x += big_size;
        break;
    default:
        break;
    }

    auto it = std::find_if(objects.begin(), objects.end(), [&x, &y] (shared_ptr<Object> o) {
        
        if(o->get_coords().x != x || o->get_coords().y != y || o->get_identity() == "Rat")
        {
            return false;
        }
        return true;
    });

    shared_ptr<Object> o{*it};
    return handle_collision(o);
}

Vector2f Rat::move()
{
    Vector2f movement{};
    switch (direction)
    {
        case 'w':
            movement.y -= 1;
            break;
        case 'a':
            movement.x -= 1;
            break;
        case 's':
            movement.y += 1;
            break;
        case 'd':
            movement.x += 1;
            break;
    };

    return movement;
}

void Rat::change_direction(sf::Event::KeyEvent e)
{
    if (e.code == sf::Keyboard::Up || e.code == sf::Keyboard::W)
    {
        upcoming_direction = 'w';
    } 
    else if (e.code == sf::Keyboard::Right || e.code == sf::Keyboard::D)
    {
        upcoming_direction = 'd';
    } 
    else if (e.code == sf::Keyboard::Left || e.code == sf::Keyboard::A)
    {
        upcoming_direction = 'a';
    } 
    else if (e.code == sf::Keyboard::Down || e.code == sf::Keyboard::S)
    {
        upcoming_direction = 's';
    }
    direction = upcoming_direction;
}


void Rat::update(Time & delta)
{
    if(!alive)
    {
        return;
    }
    
    Vector2f new_coords{coords};
    
    if(can_move(new_coords))
    {
        Vector2f movement{move()};
        {
            float distance{speed * delta.asSeconds()};
            coords += movement * distance;
            
            fix_coordinates();
        }
        
    }   

}