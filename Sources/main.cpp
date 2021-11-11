#include <SFML/Window.hpp>
#include "Registry.hpp"
#include "components.hpp"
#include "systems.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    Registry registry(1);
    component::position_s pos = {50, 50};
    component::velocity_s vel = {1, 1};
    component::drawable_s sprite;
    sprite.texture.loadFromFile("../canard.png");
    sprite.sprite.setTexture(sprite.texture, true);
    sprite.window = &window;
    sprite.sprite.setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
    sprite.sprite.setScale((float)0.3, (float)0.3);
    component::controllable_s ctrl = {true};
    registry.registerComponent<component::position_s>([](Registry &, Entity const &){}, [](Registry &, Entity const &){});
    registry.registerComponent<component::velocity_s>([](Registry &, Entity const &){}, [](Registry &, Entity const &){});
    registry.registerComponent<component::drawable_s>([](Registry &, Entity const &){}, [](Registry &, Entity const &){});
    registry.registerComponent<component::controllable_s>([](Registry &, Entity const &){}, [](Registry &, Entity const &){});
    registry.addComponent<component::position_s>(registry.entityFromIndex(0), std::move(pos));
    registry.addComponent<component::velocity_s>(registry.entityFromIndex(0), std::move(vel));
    registry.addComponent<component::controllable_s>(registry.entityFromIndex(0), std::move(ctrl));
    registry.addComponent<component::drawable_s>(registry.entityFromIndex(0), std::move(sprite));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear(sf::Color::Black);
        logging_system(registry);
        control_system(registry);
        position_system(registry);
        draw_system(registry);
        window.display();
    }
    return 0;
}
