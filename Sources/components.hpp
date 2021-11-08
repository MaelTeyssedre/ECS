#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include "Registry.hpp"

namespace component
{
    struct position_s {
        int x;
        int y;
    };

    struct velocity_s {
        int vx;
        int vy;
    };

    struct drawable_s {
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RenderWindow *window;
    };

    struct controllable_s {

    };
}

#endif /* !COMPONENTS_HPP_ */
