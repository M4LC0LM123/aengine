#include "headers/PhysicsBody.h"

PhysicsBody::PhysicsBody(const Entity& entity, const b2BodyType& type)
{
    this->scale = entity.scale;
    this->pos = entity.pos;
    this->type = type;
    this->density = 1.0f;
    this->friction = 0.3f;
    this->bodyDef.type = this->type;
    this->body = EntityManager::world.CreateBody(&this->bodyDef);
    this->box.SetAsBox(this->scale.x*0.5f, this->scale.y*0.5f);
    this->fixtureDef.shape = &box;
    this->fixtureDef.density = this->density;
    this->fixtureDef.friction = this->friction;
    this->body->CreateFixture(&this->fixtureDef);
    this->body->SetTransform(Vector2ToB2Vec2(this->pos), this->rotation*DEG2RAD);
    this->originX = this->scale.x*0.5f;
    this->originY = this->scale.y*0.5f;
}
void PhysicsBody::update(Entity* entity)
{
    Object::update(entity);
    this->pos = B2Vec2ToVector2(this->body->GetPosition());
    this->rotation = this->body->GetAngle()*RAD2DEG;
    entity->pos = this->pos;
    entity->scale = this->scale;
}
void PhysicsBody::render()
{
    Object::render();
}
void PhysicsBody::dispose()
{
    Object::dispose();
}
bool PhysicsBody::operator==(const PhysicsBody& other) const
{
    return this->id == other.id;
}