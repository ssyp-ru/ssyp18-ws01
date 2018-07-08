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

class Player 
    : public Unit
{
public:
    static const int16_t PLAYER_PHYSIC_TYPE = 0b10;

    Player(re::Point2f pos);
    ~Player() = default;
    
    void update();
    void display(re::Camera camera);

    void add_exp(int amount);
    int get_level() { return level; }
    void reduceCooldowns();
    virtual void onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) override;

    re::AnimationPtr movingAnim_Forward; // moving animation
    re::ResourceManager resource_manager;

private:
    int expToNextLevel[18] = { 100 };
    int exp, level, hp, maxhp;
};

