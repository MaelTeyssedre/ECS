#include "Registry.hpp"
#include "components.hpp"
#include <iostream>
#include "systems.hpp"

void logging_system(Registry &r) {
    const SparseArray<component::position_s> &positions = r.getComponents<component::position_s>();
    const SparseArray<component::velocity_s> &velocities = r.getComponents<component::velocity_s>();
    for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {
        const std::optional<component::position_s> &pos = positions[i];
        const std::optional<component::velocity_s> &vel = velocities[i];
        if (pos && vel)
            std::cerr << i << ": Position = { " << pos.value().x << ", " << pos.value().y << " }, Velocity = { " << vel.value().vx << ", " << vel.value().vy << " }" << std::endl;
    }
}

void position_system(Registry &r) {
    SparseArray<component::position_s> &positions = r.getComponents<component::position_s>();
    SparseArray<component::drawable_s> &sprite = r.getComponents<component::drawable_s>();
    for (size_t i = 0; i < positions.size() && i < sprite.size(); i++) {
        std::optional<component::drawable_s> &sprt = sprite[i];
        std::optional<component::position_s> &pos = positions[i];
        if (pos && sprt) {
            sprt.value().sprite.setPosition((float)pos.value().x, (float)pos.value().y);
            if (pos.value().x > 2000)
                pos.value().x = -300;
        }
    }
}

void draw_system(Registry &r) {
    SparseArray<component::drawable_s> &drawables = r.getComponents<component::drawable_s>();
    for (size_t i = 0; i < drawables.size(); i++) {
        std::optional<component::drawable_s> &draw = drawables[i];
        if (draw)
            draw.value().window->draw(draw.value().sprite);
    }
}

void control_system(Registry &r) {
    SparseArray<component::position_s> &positions = r.getComponents<component::position_s>();
    SparseArray<component::velocity_s> &velocities = r.getComponents<component::velocity_s>();
    SparseArray<component::controllable_s> &controllable = r.getComponents<component::controllable_s>();
    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < controllable.size(); i++) {
        std::optional<component::position_s> &pos = positions[i];
        std::optional<component::velocity_s> &vel = velocities[i];
        std::optional<component::controllable_s> &ctrl = controllable[i];
        if (ctrl && ctrl.value().isControllable && pos && vel) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                pos.value().x -= vel.value().vx;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                pos.value().x += vel.value().vx;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                pos.value().y += vel.value().vy;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                pos.value().y -= vel.value().vy;
        }
    }
}