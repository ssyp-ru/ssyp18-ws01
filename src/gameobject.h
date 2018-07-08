#pragma once

#include <RealEngine/physic_core.h>
#include <RealEngine/math.h>
#include <RealEngine/camera.h>
#include <RealEngine/graphic.h>

class GameObject {
public:
    GameObject();
    virtual ~GameObject() {}

    int get_id();

    static GameObject *get_object_by_id( int id );

    static std::map<int,class GameObject*> object_map;
private:
    int object_id_;
    static int object_count;
};