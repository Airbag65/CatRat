#include "../headers/includes/common.h"
#include "Game_State.h"
#include "Exit_State.h"

Game_State::Game_State(string s)
: object_vector{&Object::objects}, map_path{"../source/map/"}, game_image_path{Object::image_path}, chosen_level{map_path + s}
{}


sf::RectangleShape generate_health(int x, int y, sf::Texture & heart)
{
    Vector2f health_size{50, 50};
    sf::RectangleShape health{health_size};
    health.setTexture(&heart);
    health.setPosition(x, y);
    return health;
}


void Game_State::print()
{
    window.clear();
    for( shared_ptr<Object> o : *object_vector )
    {
        window.draw(o->render());
    }
    sf::RectangleShape heart1{generate_health(1325, 925, filled_heart)};
    if(player->get_health() <= 2)
    {
        heart1.setTexture(&empty_heart);
    }
    sf::RectangleShape heart2{generate_health(1425, 925, filled_heart)};

    if (player->get_health() == 1)
    {
        heart2.setTexture(&empty_heart);
    } 
    
    sf::RectangleShape heart3{generate_health(1525, 925, filled_heart)};

    window.draw(heart1);
    window.draw(heart2);
    window.draw(heart3);
    window.display();
}


void Game_State::run()
{
    read_file(chosen_level); // chosen_level är en statisk string i State
    if(!filled_heart.loadFromFile(game_image_path + "filled_heart.png"))
    {
        std::cerr << "filled heart failed to load" << endl;
    }

    if(!empty_heart.loadFromFile(game_image_path + "empty_heart.png"))
    {
        std::cerr << "empty heart failed to load" << endl;
    }

    sf::Clock clock;
    vector<shared_ptr<Movable_Object>> movable{};
    vector<shared_ptr<Cat>> cats{};
    for(shared_ptr<Object> o : *object_vector)
    {
        // Lägger till pekare till alla icke-statiska objekt i en vektor så att dynamic_cast inte ska behöva göras varje gång loopen körs
        shared_ptr<Movable_Object> mv{dynamic_pointer_cast<Movable_Object>(o)};
            if (mv != nullptr)
            {
                movable.push_back(mv);
            }
        // Sätter en pekare till spelaren för att lättare hålla koll på den och för att inte behöva göra dynamic_cast så ofta
        shared_ptr<Rat> r{dynamic_pointer_cast<Rat>(o)};
        if (r != nullptr)
        {
            player = r;
            
        }
        shared_ptr<Cat> c{dynamic_pointer_cast<Cat>(o)};
        if (c != nullptr)
        {
            cats.push_back(c);
        }
    }


    std::for_each(cats.begin(), cats.end(), [this](shared_ptr<Cat> c){ c->set_prey(player); });
    
    // Huvudsakliga spel-loopen
    while(!game_over){
        if(player->is_dead()) {
            game_over = true;
            break;
        }
        if(player->get_cheese() == total_cheeses)
        {
            string win{"you won"};
            player->set_end_message(win);
            game_over = true;
            break;
        }
        sf::Event event{};
        print();
        auto delta = clock.restart();
                
        for(shared_ptr<Movable_Object> o : movable)
        {
            o->update(delta);
        }

        // EVENT-LOOP (för tangentbords-interaktion och liknande)
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                cout << "CatRat closed successfully" << endl;
                game_over = true;
                break;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                player->change_direction(event.key);
            }
        }
    }
    window.close();
    string end{};
    if(player->cause_of_end() == "cat")
    {
        end = "death by cat it shall be";
    }
    else if(player->cause_of_end() == "rat_trap")
    {
        end = "death by rat trap it shall be";
    }
    else
    {
        end = "you won";
    }
    object_vector->clear();
    make_shared<Exit_State>(end)->run();
    
}


void Game_State::create_object(char c, int x_coord, int y_coord)
{
    float x{};
    x = x_coord;
    float y{};
    y = y_coord;
    int object_size{100};
    switch (c)
    {
        case '#':
            object_vector->push_back(make_shared<Wall>(Wall{object_size, x, y, "Wall"}));
            break;
        case '_':
            object_vector->push_back(make_shared<Wall>(Wall{object_size, x, y, "Floor"}));
            break;
        case '!':
            object_vector->push_back(make_shared<Wall>(Wall{object_size, x, y, "Floor"}));
            object_vector->push_back(make_shared<Cat>(Cat{object_size, x, y}));
            break;
        case '*':
            object_vector->push_back(make_shared<Rat_Trap>(Rat_Trap{object_size, x, y}));
            break;
        case '@':
            object_vector->push_back(make_shared<Wall>(Wall{object_size, x, y, "Floor"}));
            object_size *= 0.8;
            x = (x/0.8 + 0.1);
            y = (y/0.8 + 0.1);
            object_vector->push_back(make_shared<Rat>(Rat{object_size, x, y}));
            break;
        case '$':
            object_vector->push_back(make_shared<Cheese>(Cheese{object_size, x, y}));
            object_vector->push_back(make_shared<Wall>(Wall{object_size, x, y, "Floor"}));
            total_cheeses++;
            break;
        default:
            break;
    }   
}


void Game_State::read_file(string filename)
{
    ifstream file{filename};
    vector<Object*> obj;
    char c{};
    int x_coord{};
    int y_coord{};
    if(!file)
    { 
        std::cerr << "This file does not exist." << endl; 
        return;
    }
    
    while(!file.eof())
    {
        c = file.get();
        if( c == '\n' )
        {
            y_coord++;
            x_coord = 0;
        } else {
            create_object(c, x_coord, y_coord);
            x_coord++;
        }
    }
}