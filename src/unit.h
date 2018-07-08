#pragma once

#include <RealEngine/graphic/animation.h>
#include <cmath>
#include <iostream>
#include <RealEngine/physic_core.h>
#include "RealEngine/event.h"
#include "events/move_event.h"

#include "physgameobject.h"

class Unit 
    : public PhysGameObject
{
public:

    Unit(re::Point2f pos);
    ~Unit(){}
    virtual void attack(int target_id);
    virtual void update();
    virtual void display(re::Camera camera);

    // from Physic Engine
    virtual void onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) override;

protected:
    void go_to(re::Point2f finish_point);
    void attack_event(int target_id);

protected:
    // std::vector<Ability*> abilities;
    int hp, maxhp;
    re::Point2f goto_point;
};

