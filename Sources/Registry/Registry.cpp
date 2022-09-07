#include "Registry.hpp"

Registry::Registry(size_t nbEntity)
    : _entities(nbEntity) {}

auto Registry::spawnEntity() -> Entity
{
    if (_killedEntities.empty())
    {
        _entities++;
        for (auto i : _componentsArrays) {
            _constructorArray[i.first](*this, Entity(_entities));
        }
        return Entity(_entities - 1);
    } else {
        Entity e {_killedEntities.back()};
        for (auto i : _componentsArrays)
            _constructorArray[i.first](*this, e);
        _killedEntities.pop_back();
        return Entity(e);
    }
}

auto Registry::entityFromIndex(size_t idx) -> Entity
{
    if (idx >= _entities)
        throw std::invalid_argument("entity doesn't exit at this index");
    if (isKilled(Entity(idx)))
        throw std::invalid_argument("no alive entity at this at this index (killed)");
    return Entity(idx);
}

auto Registry::isKilled(Entity const &e) -> bool
{
    for (size_t i = 0; i < _killedEntities.size(); i++)
        if ((size_t)e == (size_t)_killedEntities[i])
            return true;
    return false;
}

auto Registry::run_system() -> void
{
    for (size_t i = 0; i < _systems.size(); i++)
        _systems[i](*this);
}