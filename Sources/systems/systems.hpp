#include "Registry.hpp"
#include "components.hpp"

void loggingSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::velocity_s> &velocities);
void controlSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::velocity_s> &velocities, SparseArray<component::controllable_s> &controllable);
void drawSystem(Registry &r, SparseArray<component::drawable_s> &drawables);
void positionSystem(Registry &r, SparseArray<component::position_s> &positions, SparseArray<component::drawable_s> &sprite);
