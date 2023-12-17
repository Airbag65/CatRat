#include "Exit_State.h"
#include "Menu_State.h"


Exit_State::Exit_State(string s) 
: exit_message{s}
{
    font.loadFromFile("../source/static/assets/ChrustyRock-ORLA.ttf");
}

void Exit_State::run()
{
    while(window.isOpen())
    {
        sf::Event event;
        print();
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                cout << "CatRat closed successfully" << endl;
                window.close();
                break;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                window.close();
                make_shared<Menu_State>()->run();
            }
        }
    }
   
}

void Exit_State::print()
{
    window.clear();
    sf::Text game_over{set_text("Game Over", 120, 150)}; // text, storlek, y-koordinat
    game_over.setFillColor(sf::Color::Red);
    if(exit_message == "you won")
    {
        game_over.setFillColor(sf::Color::Green);
    }

    sf::Text final_message{set_text(exit_message, 80, 350)}; 
    
    sf::Text information_1{set_text("Press escape to exit", 50, 550)};
    
    sf::Text information_2{set_text("Press enter to play again", 50, 650)};
    
    window.draw(game_over);
    window.draw(final_message);
    window.draw(information_1);
    window.draw(information_2);
    window.display();
}