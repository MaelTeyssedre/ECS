#include "Registry.hpp"

Registry::Registry(size_t nbEntity)
    : _entities(nbEntity) {}

Entity Registry::spawnEntity() {
    if (_killedEntities.empty()) {
        _entities++;
        for (auto i : _componentsArrays)
            _constructorArray[i.first](*this, Entity(_entities));
        return Entity(_entities);
    }
    for (auto i : _componentsArrays)
            _constructorArray[i.first](*this, Entity(_entities));
    _killedEntities.pop_back();
    return Entity(_killedEntities.size());
}

Entity Registry::entityFromIndex(size_t idx) {
    if (idx >= _entities)
        throw std::invalid_argument("entity doesn't exit at this index");
    if (isKilled(Entity(idx)))
        throw std::invalid_argument("no alive entity at this at this index (killed)");
    return Entity(idx);
}

void Registry::killEntity(Entity const &e) {
    if (e < _entities && !isKilled(e)) {
        _killedEntities.push_back(e);
        for (auto i : _componentsArrays)
            _destructorArray[i.first](*this, Entity(e));
    }
    if (e >= _entities)
        throw std::invalid_argument("entity doesn't exist");
    if (isKilled(e))
        throw std::invalid_argument("entity already killed");
}

bool Registry::isKilled(Entity const &e) {
    for (size_t i = 0; i < _killedEntities.size(); i++)
        if ((size_t)e == (size_t)_killedEntities[i])
            return true;
    return false;
}

void Registry::run_system() {
    for (size_t i = 0; i < _systems.size(); i++)
        _systems[i](*this);
}
