#include <stddef.h>
#include "Entity.hpp"

ecs::Entity::Entity(size_t id)
    : _id(id){};

ecs::Entity::operator size_t() const
{
    return _id;
}
