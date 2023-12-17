#include "State.h"
#pragma once

class Exit_State : public State
{
public:
    Exit_State(string s);
    
    void print() override;
    void run() override;
    void set_exit(string s){exit_message = s;}
private:
    string exit_message;
};