#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_

    #include "ECS.hpp"
    #include "components.hpp"

    void loggingSystem(ecs::Registry &r, ecs::SparseArray<component::position_s> &positions, ecs::SparseArray<component::velocity_s> &velocities) {
        (void)r;
        return;
        for (auto &&[pos, vel] : ecs::Zipper(positions, velocities))
            std::cerr << "Position = {" << pos.x << ", " << pos.y << "}, Velocity = {" << vel.vx << ", " << vel.vy << "}" << std::endl;
    }

    void controlSystem(ecs::Registry &r, ecs::SparseArray<component::position_s> &positions, ecs::SparseArray<component::velocity_s> &velocities, ecs::SparseArray<component::controllable_s> &controllable) {
        (void)r;
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

    void drawSystem(ecs::Registry &r, ecs::SparseArray<component::drawable_s> &drawables) {
        (void)r;
        for (size_t i = 0; i < drawables.size(); i++) {
            std::optional<component::drawable_s> &draw = drawables[i];
            if (draw)
                draw.value().window->draw(draw.value().sprite);
        }
    }

    void positionSystem(ecs::Registry &r, ecs::SparseArray<component::position_s> &positions, ecs::SparseArray<component::drawable_s> &sprite) {
        (void)r;
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

#endif
