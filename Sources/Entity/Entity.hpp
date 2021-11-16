/**
 * \file Entity.hpp
 *
 * \brief file where the class Entity is defined
 */

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include <stddef.h>

    /**
     * \brief declaration of class registry to avoid circular includes...
     */
    class Registry;

    /**
     * \class Entity Entity.hpp
     * 
     * \brief class for Entity, constructable only from Registry class
     */
    class Entity {
        public:
            /**
             * \fn operator size_t() const
             * 
             * \brief overload of the operator () to be able to cast an Entity in size_t
             */
            operator size_t() const;

            /**
             * \fn ~Entity() = default
             * 
             * \brief Entity dtor
             */
            ~Entity() = default;

        protected:
            /**
             * \brief class passed in friend to only be able to be created by it
             */
            friend class Registry;

            /**
             * \fn explicit Entity(size_t id)
             * 
             * \brief ctor
             *
             * \param id id of the entity
             */
            explicit Entity(size_t id);

        private:
            size_t _id; /*! id of the entity */
    };

#endif /* !ENTITY_HPP_ */
