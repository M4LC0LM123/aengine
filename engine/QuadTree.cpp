#include "headers/QuadTree.h"
#include "headers/Entity.h"

QuadTree::QuadTree(int level, Rectangle bounds)
    : level(level), bounds(bounds)
{
    children.reserve(4);
}

void QuadTree::subdivide()
{
    float subWidth = bounds.width / 2.0f;
    float subHeight = bounds.height / 2.0f;
    float x = bounds.x;
    float y = bounds.y;

    children.emplace_back(level + 1, Rectangle{ x, y, subWidth, subHeight }); // NW
    children.emplace_back(level + 1, Rectangle{ x + subWidth, y, subWidth, subHeight }); // NE
    children.emplace_back(level + 1, Rectangle{ x, y + subHeight, subWidth, subHeight }); // SW
    children.emplace_back(level + 1, Rectangle{ x + subWidth, y + subHeight, subWidth, subHeight }); // SE
}

void QuadTree::insert(Entity* entity)
{
    if (!CheckCollisionRecs(entity->getBoundingBox(), bounds))
        return;

    if (children.empty() && entities.size() < MAX_CAPACITY)
    {
        entities.push_back(entity);
        return;
    }

    if (children.empty())
        subdivide();

    for (QuadTree& child : children)
        child.insert(entity);
}

std::vector<Entity*> QuadTree::retrieve(Rectangle area)
{
    std::vector<Entity*> foundEntities;

    if (!CheckCollisionRecs(bounds, area))
        return foundEntities;

    for (Entity* entity : entities)
    {
        if (CheckCollisionRecs(entity->getBoundingBox(), area))
            foundEntities.push_back(entity);
    }

    if (!children.empty())
    {
        for (QuadTree& child : children)
        {
            std::vector<Entity*> childEntities = child.retrieve(area);
            foundEntities.insert(foundEntities.end(), childEntities.begin(), childEntities.end());
        }
    }

    return foundEntities;
}

void QuadTree::clear()
{
    entities.clear();

    for (QuadTree& child : children)
        child.clear();

    children.clear();
}

Rectangle QuadTree::getBounds()
{
    return this->bounds;
}

void QuadTree::setBounds(Rectangle bounds)
{
    this->bounds = bounds;
}