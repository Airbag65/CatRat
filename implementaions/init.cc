#include "../headers/includes/include.h"

Object::Object(int s, float x, float y, std::string i) 
:  size{s}, coords{x * size, y * size}, identity{i} 
{} 

vector<shared_ptr<Object>> Object::objects{};
const string Object::image_path{"../source/static/images/"};

// RÖRLIGA OBJEKT
Movable_Object::Movable_Object(int s, float x, float y, int v, std::string i)
: Object(s, x, y, i), speed{v}
{}

Cat::Cat(int s, float x, float y)
: Movable_Object(s, x, y, 110, "Cat")
{
    if(!right.loadFromFile(image_path + "cat_d.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!left.loadFromFile(image_path + "cat_a.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!up.loadFromFile(image_path + "cat_w.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!down.loadFromFile(image_path + "cat_s.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    
}

Rat::Rat(int s, float x, float y)
: Movable_Object(s, x, y, 200, "Rat"), health{3}, alive{true}
{
    big_size = size / .8;
    if(!right.loadFromFile(image_path + "rat_d.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!left.loadFromFile(image_path + "rat_a.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!up.loadFromFile(image_path + "rat_w.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
    if(!down.loadFromFile(image_path + "rat_s.png"))
    {
        std::cerr << "no rat loaded" << endl;
    }
}



// STATISKA OBJEKT
Static_Object::Static_Object(int s, float x, float y, std::string i)
: Object(s, x, y, i) 
{}

Cheese::Cheese(int s, float x, float y) 
: Static_Object(s, x, y, "Cheese") 
{   
    if(!texture.loadFromFile(image_path + "cheese.png"))
    {
        std::cerr << "no cheese loaded" << endl;
    }
}


Wall::Wall(int s, float x, float y, string i)
: Static_Object(s, x, y, i)
{}

Rat_Trap::Rat_Trap(int s, float x, float y)
: Static_Object(s, x, y, "Rat_Trap"), damage{1}, activated{false}
{
    if(!texture.loadFromFile(image_path + "rattrap.png"))
    {
        std::cerr << "no rat trap loaded" << endl;
    }

    if(!activated_texture.loadFromFile(image_path + "activated_rat_trap.png"))
    {
        std::cerr << "activated rat trap did not load" << endl;
    }
}