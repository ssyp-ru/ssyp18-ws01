#include "gameobject.h"

std::map<int,GameObject*> GameObject::object_map;
int GameObject::object_count = 0;

GameObject::GameObject() {
    this->object_id_ = object_count;
    object_count++;
    GameObject::object_map[object_id_] = this;
}

int GameObject::get_id() {
    return this->object_id_;
}

GameObject *GameObject::get_object_by_id( int id ) {
    return object_map[id];
}