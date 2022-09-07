#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Registry.hpp"
#include "components.hpp"
#include "systems.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    // * Registry
    Registry registry(1);
    // * Components creation
    component::position_s pos {50, 50};
    component::velocity_s vel {1, 1};
    component::drawable_s sprite;
    sprite.texture.loadFromFile("./canard.png");
    sprite.sprite.setTexture(sprite.texture, true);
    sprite.window = &window;
    sprite.sprite.setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
    sprite.sprite.setScale((float)0.3, (float)0.3);
    component::controllable_s ctrl {true};
    // * RegisterComponent
    registry.registerComponent<component::position_s>([](Registry &, Entity const &) -> void {}, [](Registry &, Entity const &) -> void {});
    registry.registerComponent<component::velocity_s>([](Registry &, Entity const &) -> void {}, [](Registry &, Entity const &) -> void {});
    registry.registerComponent<component::drawable_s>([](Registry &, Entity const &) -> void {}, [](Registry &, Entity const &) -> void {});
    registry.registerComponent<component::controllable_s>([](Registry &, Entity const &) -> void {}, [](Registry &, Entity const &) -> void {});
    // * AddComponent
    registry.addComponent<component::position_s>(registry.entityFromIndex(0), std::move(pos));
    registry.addComponent<component::velocity_s>(registry.entityFromIndex(0), std::move(vel));
    registry.addComponent<component::controllable_s>(registry.entityFromIndex(0), std::move(ctrl));
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
