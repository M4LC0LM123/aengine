#pragma once
#include "vector"
#include "Entity.h"

class QuadTree
{
    private:
        static const int MAX_CAPACITY = 15; // Maximum number of entities per quad
        static const int MAX_LEVELS = 6;   // Maximum levels of subdivision

        int level;
        std::vector<Entity*> entities;
        Rectangle bounds;
        std::vector<QuadTree> children;

        void subdivide();

    public:
        QuadTree(int level, Rectangle bounds);
        void insert(Entity* entity);
        std::vector<Entity*> retrieve(Rectangle area);
        void clear();
};