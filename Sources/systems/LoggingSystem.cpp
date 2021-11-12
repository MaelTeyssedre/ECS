/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** LoggingSystem
*/

#include "LoggingSystem.hpp"
#include "Registry.hpp"
#include "components.hpp"

LoggingSystem::LoggingSystem(std::function<void(Registry &)> const &f) {
    fn = f;
}

LoggingSystem::LoggingSystem(std::function<void(Registry &)> &&f) {
    fn = f;
}

void LoggingSystem::operator()(Registry &r) {
    fn(r);
}
