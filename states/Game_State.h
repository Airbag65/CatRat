#include "State.h"
#include "../headers/includes/include.h"
#pragma once

class Game_State : public State
{
    public:
        Game_State(string s);
        
        bool game_over = false;

        void print() override;
        void run() override;
        void read_file(string);
        void create_object(char, int, int);

        vector<shared_ptr<Object>>* object_vector;
    private:
        const string map_path;
        const string game_image_path;
        const string chosen_level;

        shared_ptr<Rat> player{};
        
        int total_cheeses{};

        sf::Texture filled_heart;
        sf::Texture empty_heart;
};