#include "headers/PhysicsBody3D.h"
#include "headers/EntityManager.h"
#include "headers/Entity.h"
#include "headers/Object3D.h"
#include "raylib.h"

PhysicsBody3D::PhysicsBody3D(Entity* entity, rp3d::BodyType type) : Object3D(entity)
{
    this->shape = EntityManager::physicsCommon.createBoxShape(rp3d::Vector3(entity->scale.x/2, entity->scale.y/2, entity->scale.z/2));
    this->transform.setPosition(rp3d::Vector3(entity->pos.x, entity->pos.y, entity->pos.z));
    this->body = EntityManager::world3D->createRigidBody(this->transform);
    this->body->addCollider(this->shape, rp3d::Transform::identity());
    this->body->setType(type);
    this->body->setMass(1.0f);
}

PhysicsBody3D::PhysicsBody3D(Entity* entity) : Object3D(entity)
{
    this->shape = EntityManager::physicsCommon.createBoxShape(rp3d::Vector3(entity->scale.x/2, entity->scale.y/2, entity->scale.z/2));
    this->transform.setPosition(rp3d::Vector3(entity->pos.x, entity->pos.y, entity->pos.z));
    this->body = EntityManager::world3D->createRigidBody(this->transform);
    this->body->addCollider(this->shape, rp3d::Transform::identity());
    this->body->setMass(1.0f);
}

// void PhysicsBody3D::setColliderFromModel(Model model)
// {
//     // Create collision shape from the model's mesh
//     rp3d::ConvexMesh* convexMesh = EntityManager::physicsCommon.createConvexMesh();

//     // Populate the convex mesh with vertex data from the model
//     Mesh mesh = model.meshes[0];
//     for (int i = 0; i < mesh.vertexCount; i += 3) {
//         float x = mesh.vertices[i];
//         float y = mesh.vertices[i + 1];
//         float z = mesh.vertices[i + 2];
//         convexMesh->addVertex(rp3d::Vector3(x, y, z));
//     }

//     // Create a collision shape from the convex mesh
//     rp3d::ConvexMeshShape shape(convexMesh);

//     this->body->removeCollider(this->body->getCollider(0));
//     this->body->addCollider(shape, rp3d::Transform::identity());
// }

void PhysicsBody3D::update(Entity* entity)
{
    Object3D::update(entity);
    this->pos = {this->body->getTransform().getPosition().x, this->body->getTransform().getPosition().y, this->body->getTransform().getPosition().z};
    this->rotation = {this->body->getTransform().getOrientation().x * RAD2DEG, this->body->getTransform().getOrientation().y * RAD2DEG, this->body->getTransform().getOrientation().z * RAD2DEG};
    entity->pos = this->pos;
    entity->scale = this->scale;
    entity->rotation = this->rotation;
}

void PhysicsBody3D::render()
{
    Object3D::render();
}

void PhysicsBody3D::dispose()
{
    Object3D::dispose();
}

bool PhysicsBody3D::operator==(const PhysicsBody3D& other) const
{
    return this->id == other.id;
}