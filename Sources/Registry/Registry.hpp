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
    public:
        template <class Component>
        SparseArray<Component> &registerComponent(std::function<void(Registry &, Entity const &)> constructor, std::function<void(Registry &, Entity const &)> destructor) {
            std::any any = SparseArray<Component>(_entities);
            _componentsArrays.insert(std::make_pair(std::type_index(typeid(Component)), any));
            _constructorArray.insert(std::make_pair(std::type_index(typeid(Component)), constructor));
            _destructorArray.insert(std::make_pair(std::type_index(typeid(Component)), destructor));
            return std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
        }

        template <class Component>
        SparseArray<Component> &getComponents() {
            return std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
        }

        template <class Component>
        SparseArray<Component> const &getComponents() const {
            return std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
        }

        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c) {
            SparseArray<Component> array = std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
            array.insertAt(to, c);
        }

        template <typename Component, typename ...Params>
        typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&...p) {
            SparseArray<Component> array = std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
            array.emplaceAt(to, p);
        }

        template <typename Component>
        void removeComponent(Entity const &from) {
            SparseArray<Component> array = std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))]);
            array.erase(from);
        }

    private:
        std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _constructorArray;
        std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _destructorArray;
        std::map<std::type_index, std::any> _componentsArrays;
        size_t _entities;
        std::vector<Entity> _killedEntities;
};

#endif /* !REGISTRY_HPP_ */
