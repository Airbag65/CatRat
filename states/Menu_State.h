#include "State.h"
#pragma once

class Menu_State : public State
{
public:
    Menu_State();

    void print() override;
    void run() override;
private:
    using Action = std::function<shared_ptr<State>()>;
    struct Option
    {
        sf::Text text;

        Action action;
    };

    vector<Option> options{};
    
    void add(string const&, Action);
};