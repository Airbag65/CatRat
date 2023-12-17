#include "../includes/common.h"
#pragma once



class Object
{
    public:
        virtual ~Object() = default;
        Object(int s, float x, float y, string i);

        string get_identity(){ return identity; }
        static const string image_path;
        
        Vector2f get_coords(){ return coords; }
        
        sf::RectangleShape generate_shape();
        virtual sf::RectangleShape render() = 0;
        
        static vector<shared_ptr<Object>> objects;

    protected:
        const int size; 
        
        const string identity;
        
        Vector2f coords;
        
        sf::RectangleShape shape{generate_shape()};
        
        sf::Texture texture;

        
};