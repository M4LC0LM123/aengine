#include "raylib.h"
#include "headers/Component.h"
#include "headers/Object3D.h"
#include "headers/Entity.h"

Object3D::Object3D(Entity* entity)
{
    this->pos = entity->pos;
    this->scale = entity->scale;
    this->rotation = entity->rotation;
    this->modelPos = {0, 0, 0};
    this->modelScale = {0, 0, 0};
    this->modelRotation = {0, 0, 0};
    this->cuboid = {0, 0, 0, 0, 0, 0};
    this->m_modelOnPos = true;
}

bool Object3D::isColliding(Object3D* other)
{
    return CheckCollisionCuboids(this->cuboid, other->cuboid);
}

void Object3D::update(Entity* entity)
{
    Component::update(entity);
    entity->pos = this->pos;
    entity->scale = this->scale;
    entity->rotation = this->rotation;
    this->cuboid = {this->pos.x, this->pos.y, this->pos.z, this->scale.x, this->scale.y, this->scale.z};
    if (this->modelScale.x == 0) this->modelScale.x = this->scale.x;
    if (this->modelScale.y == 0) this->modelScale.y = this->scale.y;
    if (this->modelScale.z == 0) this->modelScale.z = this->scale.z;
    if (this->m_modelOnPos == true) this->modelPos = this->pos;
}

void Object3D::render()
{
    Component::render();
    DrawCube(this->pos, this->scale.x, this->scale.y, this->scale.z, this->color);
    DrawCuboidTexture(this->texture, this->pos, this->scale.x + 0.1f, this->scale.y + 0.1f, this->scale.z + 0.1f, this->tint);
    DrawModel(this->model, this->modelPos, this->modelScale.x, this->tint);
}

void Object3D::renderColliders()
{
    DrawCubeWires(this->pos, this->scale.x, this->scale.y, this->scale.z, colliderColor);
}

void Object3D::setModelPos(Vector3 pos)
{
    this->m_modelOnPos = false;
    this->modelPos = pos;
}

void Object3D::setModelPos(float x, float y, float z)
{
    this->m_modelOnPos = false;
    this->modelPos = {x, y, z};
}

void Object3D::modelOnCuboid()
{
    this->m_modelOnPos = true;
}

void Object3D::dispose()
{
    UnloadTexture(this->texture);
    Component::dispose();
}

bool Object3D::operator==(const Object3D& other) const
{
    return this->id == other.id;
}