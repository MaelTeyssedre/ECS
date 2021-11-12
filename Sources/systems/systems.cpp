#include "components.hpp"
#include "Registry.hpp"

void loggingSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::velocity_s> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {
        const std::optional<component::position_s> &pos = positions[i];
        const std::optional<component::velocity_s> &vel = velocities[i];
        if (pos && vel)
            std::cerr << i << ": Position = { " << pos.value().x << ", " << pos.value().y << " }, Velocity = { " << vel.value().vx << ", " << vel.value().vy << " }" << std::endl;
    }
}

void controlSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::velocity_s> &velocities, SparseArray<component::controllable_s> &controllable) {
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

void drawSystem(Registry &r, SparseArray<component::drawable_s> &drawables) {
    for (size_t i = 0; i < drawables.size(); i++) {
        std::optional<component::drawable_s> &draw = drawables[i];
        if (draw)
            draw.value().window->draw(draw.value().sprite);
    }
}

void positionSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::drawable_s> &sprite) {
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
