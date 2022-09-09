#include "Registry.hpp"

ecs::Registry::Registry(size_t nbEntity)
    : _entities(nbEntity) {}

ecs::Entity ecs::Registry::spawnEntity()
{
    if (_killedEntities.empty())
    {
        _entities++;
        for (auto it : _componentsArrays)
            _constructorArray[it.first](*this, Entity(_entities - 1));
        return Entity(_entities - 1);
    }
    else
    {
        Entity e{_killedEntities.back()};
        for (auto it : _componentsArrays)
            _constructorArray[it.first](*this, e);
        _killedEntities.pop_back();
        return Entity(e);
    }
}

ecs::Entity ecs::Registry::entityFromIndex(size_t idx)
{
    if (idx >= _entities)
        throw std::invalid_argument("entity doesn't exit at this index");
    if (isKilled(Entity(idx)))
        throw std::invalid_argument("no alive entity at this at this index (killed)");
    return Entity(idx);
}

bool ecs::Registry::isKilled(Entity const &e)
{
    for (auto it : _killedEntities)
        if ((size_t)e == (size_t)it)
            return true;
    return false;
}

void ecs::Registry::run_system()
{
    for(auto it : _systems)
        it(*this);
}