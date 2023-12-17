#include "../headers/includes/common.h"
//#include <experimental/random>
#include <random>

#include "../headers/classes/Cat.h"

void Cat::killing_time()
{
    prey->kill();
}


Vector2i Cat::delta_coords()
{
    // Ger skillnaden i avstånd mellan katt och råtta
    int x_diff{};
    x_diff = round(prey->get_coords().x) - round(coords.x);
    int y_diff{};
    y_diff = round(prey->get_coords().y) - round(coords.y); 
    Vector2i coord_holder{x_diff, y_diff};
    return coord_holder;
}



void Cat::find_player()
{
    Vector2f delta{delta_coords()};


    if(int(coords.x)%size != 0 || int(coords.y)%size != 0)
    {
        return;
    }
    
    if(direction == 'w' && delta.y < 0)
    {
        /* Om katten redan är på väg uppåt för att den jagar en katt, 
        och katten fortfarande är åt det hållet, så fortsätter katten */
        return;
    }

    if(direction == 's' && delta.y > 10)
    {
        // Samma som ovan fast för nedåt
        return;
    }

    
    
        if(delta.x < 10)
    {
        direction = 'a';
        
        
    } else if(delta.x > 10)
    {
        direction = 'd';
    } else if(delta.x == 10)
    {
        // Om delta-x == 10, d.v.s om katten är i samma "kolumn" som råttan, så används en place-holder för riktningen
        direction = 'h'; // 'h' för 'hold'
    }
    
    if(direction != 'h')
    {
        return;
    }

    if(delta.y < 0)
    {

        direction = 'w';
    }
    else if (delta.y > 10)
    {   direction = 's';
        
    }

    
}



void Cat::set_prey(shared_ptr<Rat> const& r)
{
    if (prey == nullptr)
    {
        prey = r;
    }
}

bool Cat::handle_collision(shared_ptr<Object> & o)
{
    string name{o->get_identity()};
    if (name == "Wall")
    {
        coords.x = round(coords.x);
        if(int(coords.x)%size != 0)
        {
            if(int(coords.x)%size <=2)
            {
                coords.x -= int(coords.x)%size;
            }
            else if(int(coords.x)%size >=97)
            {
                coords.x += size-int(coords.x)%size;
            }
            
            
        }
        coords.y = round(coords.y);
        if(int(coords.y)%size != 0 && int(coords.y)%size <=2)
        {
            coords.y -= int(coords.y)%size;
            
            
        }
        direction = 'h';
        find_player();
        return false;
    }
    return true;
}


bool Cat::can_move(Vector2f const& new_coords)
{
    int x{int(new_coords.x)}; 
    x -= (x % size); 
    
    
    int y{int(new_coords.y)};
    y -= (y % size);

    Vector2f rat_coords{prey->get_coords()};

    switch (direction)
    {
    case 's':
        y += size;
        break;
    case 'd':
        x += size;
        break;
    default:
        break;
    }

    auto it = std::find_if(objects.begin(), objects.end()-1, [&x, &y] (shared_ptr<Object> o) {
        
        if(o->get_coords().x != x || o->get_coords().y != y || o->get_identity() == "Cat")
        {
            return false;
        }
        return true;
    });


   shared_ptr<Object> o{*it};
    return handle_collision(o);
}

Vector2f Cat::move()
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
        default:
            break;
    };

    return movement;
}

bool Cat::rat_is_dead()
{
    Vector2f delta{delta_coords()};
    prey->set_end_message("cat");

    if(delta.x >= 10 && delta.x < size-20 && abs(delta.y) < size*0.3)
    {
        return true;
    }
    return false;
}


void Cat::update(Time & delta)
{
    if(rat_is_dead())
    {
        killing_time();
        return;
    }
    else{
        find_player();
    }

    Vector2f new_coords{coords};
    if(can_move(new_coords))
    {
        Vector2f movement{move()};
        {
            float distance{speed * delta.asSeconds()};
            coords += movement * distance;
            
        }
        
    } 
    
}