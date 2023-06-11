#ifndef PREFAB_H
#define PREFAB_H
#pragma once
#include "fstream"
#include "sstream"
#include "Entity.h"
#include "raylib.h"

unsigned char floatToChar(float value);

void LoadPrefab(Entity* entity, std::string prefab)
{
    float x;
    float y;
    float w;
    float h;
    float rotation;
    std::string components;
    float r, g, b, a;
    float tr, tg, tb, ta;
    std::string texture;
    float frame;
    float fw;
    float fh;
    bool bounce;
    float gravity;
    float mass;
    float friction;
    std::ifstream infile(prefab);
    if (infile.is_open()) 
    {
        infile >> x;
        infile >> y;
        infile >> w;
        infile >> h;
        infile >> rotation;
        infile >> components;
        infile >> r;
        infile >> g;
        infile >> b;
        infile >> a;
        infile >> tr;
        infile >> tg;
        infile >> tb;
        infile >> ta;
        infile >> texture;
        infile >> frame;
        infile >> fw;
        infile >> fh;
        infile >> bounce;
        infile >> gravity;
        infile >> mass;
        infile >> friction;
        infile.close();
    }
    if (components.find("Object") != std::string::npos) entity->addComponent<Object>();
    if (components.find("Body") != std::string::npos && !(components.find("KinematicBody") != std::string::npos || components.find("RigidBody") != std::string::npos || components.find("StaticBody") != std::string::npos)) 
        entity->addComponent<Body>();
    if (components.find("KinematicBody") != std::string::npos) entity->addComponent<KinematicBody>();
    if (components.find("RigidBody") != std::string::npos) entity->addComponent<RigidBody>();
    if (components.find("StaticBody") != std::string::npos) entity->addComponent<StaticBody>();
    entity->pos = {x, y};
    entity->scale = {w, h};
    entity->rotation = {0, 0, rotation};
    if (entity->hasComponent<Object>())
    {
        entity->getComponent<Object>()->pos = {x, y};
        entity->getComponent<Object>()->scale = {w, h};
        entity->getComponent<Object>()->rotation = rotation;
        entity->getComponent<Object>()->color = (Color) {floatToChar(r), floatToChar(g), floatToChar(b), floatToChar(a)};
        entity->getComponent<Object>()->tint = (Color) {floatToChar(tr), floatToChar(tg), floatToChar(tb), floatToChar(ta)};
        entity->getComponent<Object>()->texture = LoadTexture(texture.c_str());
        entity->getComponent<Object>()->setFrame({fw, fh}, frame);
    }
    else if (entity->hasComponent<Body>())
    {
        entity->getComponent<Body>()->pos = {x, y};
        entity->getComponent<Body>()->scale = {w, h};
        entity->getComponent<Body>()->rotation = rotation;
        entity->getComponent<Body>()->color = (Color) {floatToChar(r), floatToChar(g), floatToChar(b), floatToChar(a)};
        entity->getComponent<Body>()->tint = (Color) {floatToChar(tr), floatToChar(tg), floatToChar(tb), floatToChar(ta)};
        entity->getComponent<Body>()->texture = LoadTexture(texture.c_str());;
        entity->getComponent<Body>()->setFrame({fw, fh}, frame);
    }
    else if (entity->hasComponent<KinematicBody>())
    {
        entity->getComponent<KinematicBody>()->pos = {x, y};
        entity->getComponent<KinematicBody>()->scale = {w, h};
        entity->getComponent<KinematicBody>()->rotation = rotation;
        entity->getComponent<KinematicBody>()->color = (Color) {floatToChar(r), floatToChar(g), floatToChar(b), floatToChar(a)};
        entity->getComponent<KinematicBody>()->tint = (Color) {floatToChar(tr), floatToChar(tg), floatToChar(tb), floatToChar(ta)};
        entity->getComponent<KinematicBody>()->texture = LoadTexture(texture.c_str());;
        entity->getComponent<KinematicBody>()->setFrame({fw, fh}, frame);
        entity->getComponent<KinematicBody>()->bounce = bounce;
    }
    else if (entity->hasComponent<RigidBody>())
    {
        entity->getComponent<RigidBody>()->pos = {x, y};
        entity->getComponent<RigidBody>()->scale = {w, h};
        entity->getComponent<RigidBody>()->rotation = rotation;
        entity->getComponent<RigidBody>()->color = (Color) {floatToChar(r), floatToChar(g), floatToChar(b), floatToChar(a)};
        entity->getComponent<RigidBody>()->tint = (Color) {floatToChar(tr), floatToChar(tg), floatToChar(tb), floatToChar(ta)};
        entity->getComponent<RigidBody>()->texture = LoadTexture(texture.c_str());;
        entity->getComponent<RigidBody>()->setFrame({fw, fh}, frame);
        entity->getComponent<RigidBody>()->gravity = gravity;
        entity->getComponent<RigidBody>()->mass = mass;
    }
    else if (entity->hasComponent<StaticBody>())
    {
        entity->getComponent<StaticBody>()->pos = {x, y};
        entity->getComponent<StaticBody>()->scale = {w, h};
        entity->getComponent<StaticBody>()->rotation = rotation;
        entity->getComponent<StaticBody>()->color = (Color) {floatToChar(r), floatToChar(g), floatToChar(b), floatToChar(a)};
        entity->getComponent<StaticBody>()->tint = (Color) {floatToChar(tr), floatToChar(tg), floatToChar(tb), floatToChar(ta)};
        entity->getComponent<StaticBody>()->texture = LoadTexture(texture.c_str());;
        entity->getComponent<StaticBody>()->setFrame({fw, fh}, frame);
        entity->getComponent<StaticBody>()->friction = friction;
    }
}

unsigned char floatToChar(float value)
{
    return static_cast<unsigned char>(value);
}

#endif