#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ECS.hpp"
#include "components.hpp"
#include "systems.hpp"

int main() {
    std::function ctor {[](ecs::Registry &, ecs::Entity const &) -> void {}};
    std::function dtor {[](ecs::Registry &, ecs::Entity const &) -> void {}};
    sf::RenderWindow window(sf::VideoMode(1800, 900), "My Window");
    // * Registry
    ecs::Registry registry;
    registry.spawnEntity();
    registry.spawnEntity();
    registry.spawnEntity();
    // * Components creation
    component::position_t pos {50, 50};
    component::drawable_t sprite;
    sprite.window = &window;
    sprite.texture.loadFromFile("./canard.png");
    sprite.sprite.setTexture(sprite.texture, true);
    sprite.sprite.setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
    sprite.sprite.setScale((float)0.3, (float)0.3);
    // * RegisterComponent
    registry.registerComponent<component::position_s>(ctor, dtor);
    registry.registerComponent<component::velocity_s>(ctor, dtor);
    registry.registerComponent<component::drawable_s>(ctor, dtor);
    registry.registerComponent<component::controllable_s>(ctor, dtor);
    // * AddComponent
    registry.addComponent<component::position_s>(registry.entityFromIndex(0), std::move(pos));
    registry.addComponent<component::velocity_s>(registry.entityFromIndex(0), {1, 1});
    registry.addComponent<component::controllable_s>(registry.entityFromIndex(0), {true});
    registry.addComponent<component::drawable_s>(registry.entityFromIndex(0), std::move(sprite));
    // * addSystem
    registry.addSystem(loggingSystem, registry.getComponents<component::position_s>(), registry.getComponents<component::velocity_s>());
    registry.addSystem(positionSystem, registry.getComponents<component::position_s>(), registry.getComponents<component::drawable_s>());
    registry.addSystem(controlSystem, registry.getComponents<component::position_s>(), registry.getComponents<component::velocity_s>(), registry.getComponents<component::controllable_s>());
    registry.addSystem(drawSystem, registry.getComponents<component::drawable_s>());
    // * mainLoop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear(sf::Color::Black);
        registry.run_system();
        window.display();
    }

    return 0;
}
