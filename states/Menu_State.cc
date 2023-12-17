#include "Menu_State.h"
#include "Game_State.h"

Menu_State::Menu_State() {font.loadFromFile("../source/static/assets/ChrustyRock-ORLA.ttf");}

void Menu_State::run()
{
    sf::Event event{};
    add("Level 1", [](){ return std::make_shared<Game_State>("1.catrat");});
    add("Level 2", [](){ return std::make_shared<Game_State>("2.catrat");});

    while(window.isOpen())
    {
        print(); 
       
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                cout << "CatRat closed successfully" << endl;
                window.close();
                break;
            } 
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
            {
                window.close();
                options.at(0).action()->run(); 
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
            {
                window.close();
                options.at(1).action()->run();
            }
        }
    }
}

void Menu_State::add(string const& text, Action action)
{
    options.push_back({sf::Text{text, font, 60}, action});
}

void Menu_State::print()
{
    window.clear();
    sf::Text catrat{set_text("CatRat", 100, 80)}; // text, storlek, y-koordinat
    catrat.setFillColor(sf::Color::Red);
    sf::Text choose_level{set_text("Choose a level", 50, 200)};
    sf::Text instruction{set_text("Click the corresponding number key on your keyboard", 40, 300)};
    window.draw(instruction);
    window.draw(choose_level);
    window.draw(catrat);
    float y{400};

    for(Option& o : options)
    {
        o.text = set_text(o.text.getString(), 60, y);
        y += o.text.getLocalBounds().height*2;
        o.text.setFillColor(sf::Color::Green);
        window.draw(o.text);
    }

    window.display();
}