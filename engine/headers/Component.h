#ifndef COMPONENT_H
#define COMPONENT_H
#pragma once

class Component
{
    public:
        Component();
        virtual ~Component() = default;
        virtual void update(Entity* entity);
        virtual void render();
        virtual void dispose();
        bool operator==(const Component& other) const;

    private:
        int id;
};

#endif