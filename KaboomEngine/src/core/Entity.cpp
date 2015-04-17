#include "Entity.h"

Entity::Entity(unsigned int id)
    : id(id) {
}

Entity::~Entity() {
}

void Entity::attachComponent(Component *component) {
    component->setParentEntity(this);
    components[&typeid(*component)] = component;
}

unsigned int Entity::getId() const {
    return id;
}