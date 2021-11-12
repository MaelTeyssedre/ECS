#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

    #include "SparseArray.hpp"
    #include <map>
    #include <typeindex>
    #include "Entity.hpp"
    #include <any>
    #include <functional>

    class Registry {
        public:
            explicit Registry() = default;
            explicit Registry(size_t nbEntity);
            virtual ~Registry() = default;
        public:
            bool isKilled(Entity const &e);
            Entity spawnEntity();
            Entity entityFromIndex(size_t idx);
            void killEntity(Entity const &e);
            void run_system();
        public:
            template <class Component>
            SparseArray<Component> &registerComponent(std::function<void(Registry &, Entity const &)> constructor, std::function<void(Registry &, Entity const &)> destructor) {
                _componentsArrays.try_emplace(std::type_index(typeid(Component)), std::make_any<SparseArray<Component>>(_entities));
                _constructorArray.insert(std::make_pair(std::type_index(typeid(Component)), constructor));
                _destructorArray.insert(std::make_pair(std::type_index(typeid(Component)), destructor));
                return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
            }

            template <class Component>
            SparseArray<Component> &getComponents() {
                return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
            }

            template <class Component>
            SparseArray<Component> const &getComponents() const {
                return std::any_cast<SparseArray<Component> const &>(_componentsArrays[std::type_index(typeid(Component))]);
            }

            template <typename Component>
            typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c) {
                return (std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])).insertAt(to, c);
            }

            template <typename Component, typename ...Params>
            typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&...p) {
                return (std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))])).emplaceAt(to, p);
            }

            template <typename Component>
            void removeComponent(Entity const &from) {
                auto array = std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
                array.erase(from);
            }

            template <typename Function, class ...Components>
            void addSystem(Function &&f, Components &&...components) {
                _systems.push_back([&f, &components...](Registry &r) -> void {
                    f(r, components...);
                });
            }

            template <typename Function, class ...Components>
            void addSystem(Function const &f, Components &...components) {
                _systems.push_back([&f, &components...](Registry &r) -> void {
                    f(r, components...);
                });
            }

        private:
            std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _constructorArray;
            std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _destructorArray;
            std::map<std::type_index, std::any> _componentsArrays;
            std::vector<std::function<void(Registry &)>> _systems;
            size_t _entities;
            std::vector<Entity> _killedEntities;
    };

#endif /* !REGISTRY_HPP_ */
