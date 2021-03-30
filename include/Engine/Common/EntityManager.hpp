#pragma once

#include <Entity.hpp>
#include <EntityManager.hpp>
#include <Pool.hpp>

class EntityManager {
    public:
        EntityManager(size_t arena_size) : entityPool(256) {};
        
    private:
        minipool<Entity> entityPool;
}