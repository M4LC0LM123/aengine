#ifndef OBJECT3D_H
#define OBJECT3D_H
#pragma once
#include "raylib.h"
#include "Cuboid.h"

class Object3D : public Component
{
    public:
        Vector3 pos;
        Vector3 scale;
        Vector3 rotation;
        Color color = WHITE;
        Color tint = WHITE;
        Texture2D texture;
        Model model;
        Vector3 modelPos;
        Vector3 modelScale;
        Vector3 modelRotation;
        Cuboid cuboid;

    Object3D(Entity* entity);
    virtual ~Object3D() = default;
    virtual bool isColliding(Object3D* other);
    virtual void update(Entity* entity) override;
    virtual void render() override;
    virtual void renderColliders();
    virtual void setModelPos(Vector3 pos);
    virtual void setModelPos(float x, float y, float z);
    virtual void modelOnCuboid();
    virtual void dispose() override;
    bool operator==(const Object3D& other) const;

    private:
        int id;

        bool m_modelOnPos;

};

#endif