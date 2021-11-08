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
            std::cerr << i << ": Position = { " << pos.value().x << ', ' << pos.value().y << " }, Velocity = { " << vel.value().vx << " }" << std::endl;
    }
}

void position_system(Registry &r) {
    SparseArray<component::position_s> &positions = r.getComponents<component::position_s>();
    SparseArray<component::velocity_s> &velocities = r.getComponents<component::velocity_s>();
    for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {
        std::optional<component::position_s> &pos = positions[i];
        std::optional<component::velocity_s> &vel = velocities[i];
        if (pos && vel) {
            pos.value().y += vel.value().vy;
            pos.value().x += vel.value().vx;
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