#include "headers/OcTree.h"
#include "headers/Entity.h"

OcTree::OcTree(int level, Cuboid bounds)
    : level(level), bounds(bounds)
{
    children.reserve(4);
}

void OcTree::subdivide()
{
    float subWidth = bounds.width / 2.0f;
    float subHeight = bounds.height / 2.0f;
    float subLength = bounds.length / 2.0f;
    float x = bounds.x;
    float y = bounds.y;
    float z = bounds.z;

    children.emplace_back(level + 1, Cuboid{ x, y, z, subWidth, subHeight, subLength }); // Bottom-Front-Left
    children.emplace_back(level + 1, Cuboid{ x + subWidth, y, z, subWidth, subHeight, subLength }); // Bottom-Front-Right
    children.emplace_back(level + 1, Cuboid{ x, y + subHeight, z, subWidth, subHeight, subLength }); // Bottom-Back-Left
    children.emplace_back(level + 1, Cuboid{ x + subWidth, y + subHeight, z, subWidth, subHeight, subLength }); // Bottom-Back-Right
    children.emplace_back(level + 1, Cuboid{ x, y, z + subLength, subWidth, subHeight, subLength }); // Top-Front-Left
    children.emplace_back(level + 1, Cuboid{ x + subWidth, y, z + subLength, subWidth, subHeight, subLength }); // Top-Front-Right
    children.emplace_back(level + 1, Cuboid{ x, y + subHeight, z + subLength, subWidth, subHeight, subLength }); // Top-Back-Left
    children.emplace_back(level + 1, Cuboid{ x + subWidth, y + subHeight, z + subLength, subWidth, subHeight, subLength }); // Top-Back-Right
}

void OcTree::insert(Entity* entity)
{
    if (!CheckCollisionCuboids(entity->getBoundingCuboid(), bounds))
        return;

    if (children.empty() && entities.size() < MAX_CAPACITY)
    {
        entities.push_back(entity);
        return;
    }

    if (children.empty())
        subdivide();

    for (OcTree& child : children)
        child.insert(entity);
}

std::vector<Entity*> OcTree::retrieve(Cuboid area)
{
    std::vector<Entity*> foundEntities;

    if (!CheckCollisionCuboids(bounds, area))
        return foundEntities;

    for (Entity* entity : entities)
    {
        if (CheckCollisionCuboids(entity->getBoundingCuboid(), area))
            foundEntities.push_back(entity);
    }

    if (!children.empty())
    {
        for (OcTree& child : children)
        {
            std::vector<Entity*> childEntities = child.retrieve(area);
            foundEntities.insert(foundEntities.end(), childEntities.begin(), childEntities.end());
        }
    }

    return foundEntities;
}

void OcTree::clear()
{
    entities.clear();

    for (OcTree& child : children)
        child.clear();

    children.clear();
}

Cuboid OcTree::getBounds()
{
    return this->bounds;
}

void OcTree::setBounds(Cuboid bounds)
{
    this->bounds = bounds;
}