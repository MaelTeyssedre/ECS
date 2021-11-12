/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** LoggingSystem
*/

#ifndef LOGGINGSYSTEM_HPP_
#define LOGGINGSYSTEM_HPP_

#include "Registry.hpp"
#include <functional>

class LoggingSystem {
    public:
        LoggingSystem(std::function<void(Registry &)> const &);
        LoggingSystem(std::function<void(Registry &)> &&);
        ~LoggingSystem() = default;
        void operator()(Registry &);
    private:
        std::function<void(Registry &)> fn;
};

#endif /* !LOGGINGSYSTEM_HPP_ */
