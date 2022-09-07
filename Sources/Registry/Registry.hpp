/**
 * \file Registry.hpp
 *
 * \brief file where the Registry class is defined
 */

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

    #include "SparseArray.hpp"
    #include <map>
    #include <typeindex>
    #include "Entity.hpp"
    #include <any>
    #include <functional>

    /**
     * \class Registry Registry.hpp
     * 
     * \brief Registry of the ECS
     */
    class Registry {
        public:
            /**
             * \fn explicit Registry() = default
             * 
             * \brief default ctor
             */
            explicit Registry() = default;

            /**
             * \fn explicit Registry(size_t nbEntity)
             * 
             * \brief ctor with an default number of entities
             */
            explicit Registry(size_t nbEntity);

            /**
             * \fn virtual ~Registry() = default
             * 
             * \brief default dtor
             */
            virtual ~Registry() = default;

        public:
            /**
             * \fn auto isKilled(Entity const &e) -> bool
             * 
             * \brief boolean function to know if an entity is already killed
             *
             * \param e constant reference to an entity
             * 
             * \return true if e is already killed, false otherwise
             */
            auto isKilled(Entity const &e) -> bool;

            /**
             * \fn auto spawnEntity() -> Entity
             * 
             * \brief create a new entity
             *
             * \return the new entity
             */
            auto spawnEntity() -> Entity;

            /**
             * \fn auto entityFromIndex(size_t idx) -> Entity
             * 
             * \brief getter of an entity from his index
             *
             * \param idx index of the entity we want to get
             * 
             * \return the entity at the specified index
             */
            auto entityFromIndex(size_t idx) -> Entity;

            /**
             * \fn auto killEntity(Entity const& e) -> void
             * 
             * \brief kill an intity
             *
             * \param e entity we want to kill
             */
            auto killEntity(Entity const& e) -> void
            {
                if (isKilled(e))
                    throw std::invalid_argument("entity already killed");
                if (e < _entities && !isKilled(e))
                {

                    _killedEntities.push_back(e);
                    for (auto i : _componentsArrays) {
                        _destructorArray[i.first](*this, Entity(e));
                    }
                }
                if (e >= _entities)
                    throw std::invalid_argument("entity doesn't exist");
            }

            /**
             * \fn auto run_system() -> void
             * 
             * \brief run all the systems in the order they are stocked
             */
            auto run_system() -> void;

        public:

            /**
             * \fn template <class Component> auto registerComponent(std::function<void(Registry &, Entity const &)> constructor, std::function<void(Registry &, Entity const &)> destructor) -> SparseArray<Component>&
             * 
             * \brief register a component in the registry
             *
             * \tparam Component type of the component we want to register
             * 
             * \param constructor function that will be the default ctor of the component, called at spawnEntity
             * \param destructor function that will be the default dtor of the component, called at killEntity
             * 
             * \return reference to the sparseArray of the component
             */
            template <class Component>
            auto registerComponent(std::function<void(Registry &, Entity const &)> constructor, std::function<void(Registry &, Entity const &)> destructor) -> SparseArray<Component>&
            {
                _componentsArrays.try_emplace(std::type_index(typeid(Component)), std::make_any<SparseArray<Component>>(_entities));
                _constructorArray.insert(std::make_pair(std::type_index(typeid(Component)), constructor));
                _destructorArray.insert(std::make_pair(std::type_index(typeid(Component)), destructor));
                return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
            }

            /**
             * \fn template <class Component> auto getComponents() -> SparseArray<Component>&
             * 
             * \brief getter for sparseArray of the component
             * 
             * \tparam Component type of component we want to get
             *
             * \return reference to the SparseArray of the component type 
             */
            template <class Component>
            auto getComponents() -> SparseArray<Component>&
            {
                return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
            }

            /**
             * \fn template <class Component> auto getComponents() const -> SparseArray<Component> const&
            {
             * 
             * \brief getter for sparseArray of the component
             * 
             * \tparam Component type of component we want to get
             *
             * \return constant reference to the SparseArray of the component type 
             */
            template <class Component>
            auto getComponents() const -> SparseArray<Component> const&
            {
                return std::any_cast<SparseArray<Component> const &>(_componentsArrays.at(std::type_index(typeid(Component))));
            }

            /**
             * \fn template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c)
             * 
             * \brief add a component to a entity
             * 
             * \tparam Component type of component we want to add
             *
             * \param to constant reference of the entity that will have the component
             * \param c universal reference of the component that will be moved in the sparseArray
             * 
             * \return reference to the sparseArray that contain the moved component
             */
            template <typename Component>
            auto addComponent(Entity const &to, Component &&c) -> typename SparseArray<Component>::reference_type
            {
                if ((size_t)to > (std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])).size())
                    (std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])).extend((size_t)to - (std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])).size());
                return (std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])).insertAt(to, c);
            }

            /**
             * \fn template <typename Component, typename ...Params> auto emplaceComponent(Entity const &to, Params &&...p) -> typename SparseArray<Component>::reference_type
             * 
             * \brief create a component for an specified entity
             * 
             * \tparam Component type of component we want create
             * \tparam Params pack of argument to create the component
             * 
             * \param to constant reference to the entity that will have the constructed component
             * \param p universal reference of a variadic template arguments to create the new component
             * 
             * \return reference to the SparseArray containing the created component
             */
            template <typename Component, typename ...Params>
            auto emplaceComponent(Entity const &to, Params &&...p) -> typename SparseArray<Component>::reference_type {
                SparseArray<Component> &tmp = std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
                if ((size_t)to < tmp.size())
                    tmp.extend(tmp.size() - (size_t)to);
                return (std::any_cast<SparseArray<Component>>(_componentsArrays[std::type_index(typeid(Component))])).emplaceAt(to, p...);
            }

            /**
             * \fn template <typename Component> auto removeComponent(Entity const &from) -> void
             * 
             * \brief remove a component of an entity
             * 
             * \tparam Component type of the component we want to remove
             *
             * \param from constant reference to the entity where the component will be removed
             */
            template <typename Component>
            auto removeComponent(Entity const &from) -> void {
                auto array = std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))]);
                array.erase(from);
            }

            /**
             * \fn template <typename Function, class ...Components> auto addSystem(Function &&f, Components &&...components) -> void
             * 
             * \brief add a system the registry
             * 
             * \tparam Function type of function we want to move into the registry
             * \tparam Components pack of components we want to pass in argument to the previously passed function
             *
             * \param f universal reference of a function that will be moved inside the registry
             * \param components universal reference of a variadic template for arguments taken by the function moved previously
             */
            template <typename Function, class ...Components>
            auto addSystem(Function &&f, Components &&...components) -> void {
                _systems.push_back([&f, &components...](Registry &r) -> void {
                    f(r, components...);
                });
            }

            /**
             * \fn template <typename Function, class ...Components> auto addSystem(Function const &f, Components &...components) -> void
             * 
             * \brief add a system the registry
             * 
             * \tparam Function type of function we want to pass into the registry
             * \tparam Components pack of components we want to pass in argument to the previously passed function
             *
             * \param f universal reference of a function that will be added inside the registry
             * \param components variadic template for arguments taken by the function passed previously
             */
            template <typename Function, class ...Components>
            auto addSystem(Function const &f, Components &...components) -> void{
                _systems.push_back([&f, &components...](Registry &r) -> void {
                    f(r, components...);
                });
            }

        private:
            std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _constructorArray; /*! map of default constructor for components, indexed by type */
            std::map<std::type_index, std::function<void(Registry &, Entity const &)>> _destructorArray; /*! map of default destructor for components, indexed by type */
            std::map<std::type_index, std::any> _componentsArrays; /*! map of components, indexed by type */
            std::vector<std::function<void(Registry &)>> _systems; /*! list of systems that will be executed from the first to the last (the order can be important) */
            size_t _entities; /*! number of entities */
            std::vector<Entity> _killedEntities; /*! list of killed entities */
    };

#endif /* !REGISTRY_HPP_ */