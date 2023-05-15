#include "headers/Component.h"
#include "headers/toolbox.h"

// ------------------------ Component ---------------------------------
Component::Component() { }

void Component::update(Entity* entity) { }

void Component::render() { }

void Component::dispose() { }

bool Component::operator==(const Component& other) const
{
    return this->id == other.id;
}

