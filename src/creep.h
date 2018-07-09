#pragma once

#include <RealEngine/graphic/animation.h>
#include <cmath>
#include <iostream>
#include <RealEngine/physic_core.h>
#include "RealEngine/resource_manager.h"
#include "RealEngine/event.h"
#include "events/move_event.h"

#include "physgameobject.h"
#include "unit.h"
#include "waypath.h"

enum class Line { TOP, MID, BOT };

class Creep 
    : public Unit
{
public:
    static const int16_t CREEP_PHYSIC_TYPE = 0b100;

    Creep(re::Point2f pos, Side side, Line line);
    ~Creep() = default;
    
    virtual void update();
    void display(re::Camera camera);
    virtual void onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) override;

    void checkAggro();
    re::AnimationPtr movingAnim_Forward; // moving animation
    re::ResourceManager resource_manager;

private:
    void load_animation();
    int aggroRange = 1000;
    int hp, maxhp;
    Waypath waypath;
};

