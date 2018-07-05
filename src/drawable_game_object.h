#pragma once
#include <RealEngine/graphic.h>
#include <RealEngine/math.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>

class DrawableGameObject : public re::GameObject
{
public:
    DrawableGameObject(re::Point2f pos);
    virtual void display(re::Camera camera);
};
