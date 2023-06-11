#ifndef OCTREE_H
#define OCTREE_H
#pragma once

#include "vector"
#include "Entity.h"

class OcTree
{
    private:
        static const int MAX_CAPACITY = 10; // Maximum number of entities per quad
        static const int MAX_LEVELS = 6;   // Maximum levels of subdivision

        int level;
        std::vector<Entity*> entities;
        Cuboid bounds;
        std::vector<OcTree> children;

        void subdivide();

    public:
        OcTree(int level, Cuboid bounds);
        void insert(Entity* entity);
        std::vector<Entity*> retrieve(Cuboid area);
        void clear();
        Cuboid getBounds();
        void setBounds(Cuboid bounds);
};

#endif