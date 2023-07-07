#ifndef PHYSICSBODY3D_H
#define PHYSICSBODY3D_H
#pragma once
#include "raylib.h"
#include "Object3D.h"

class PhysicsBody3D : public Object3D
{
    public:
        rp3d::Transform transform;
        rp3d::CollisionShape* shape;
        rp3d::RigidBody* body;

        PhysicsBody3D(Entity* entity);
        PhysicsBody3D(Entity* entity, rp3d::BodyType);
        virtual ~PhysicsBody3D() = default;
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void dispose() override;
        // virtual void setColliderFromModel(Model model);
        bool operator==(const PhysicsBody3D& other) const;
    
    private:
        int id;
        
};

#endif