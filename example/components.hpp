#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include "ECS.hpp"

namespace component
{
    typedef struct position_s
    {
        int x;
        int y;
    } position_t;

    typedef struct velocity_s
    {
        int vx;
        int vy;
    } velocity_t;

    typedef struct drawable_s
    {
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RenderWindow *window = nullptr;
    } drawable_t;

    typedef struct controllable_s
    {
        bool isControllable;
    } controllable_t;
}

#endif
