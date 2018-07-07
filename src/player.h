#pragma once

#include <RealEngine/graphic/animation.h>
#include <cmath>
#include <iostream>
#include <RealEngine/physic_core.h>
#include "RealEngine/resource_manager.h"
#include "RealEngine/event.h"
//#include <RealEngine/time.h>
#include "drawable_game_object.h"
#include "events/move_event.h"


class Player 
    : public DrawableGameObject
    , public re::EventSubscriber
{
private:
    // std::vector<Ability*> abilities;
    int expToNextLevel[18] = { 100, 100, 150, 200, 300, 450, 500, 600, 1000, 1200, 1300, 1500, 1550, 1600, 1700, 1800, 1900, 2000 };
    int exp, level, hp, maxhp;
    re::Point2f velosity, goto_point;
public:
    Player(re::Point2f pos);
    // void tryCast(int abilityIndex);
    // void addAbility(Ability *ab);
    // std::vector<Ability*>* getAbilities();
    void addExp(int amount);
    void on_event(std::shared_ptr<re::Event> event);
    int getLevel();
    void reduceCooldowns();
    virtual void onCollisionStay(re::GameObjectPtr to, re::Vector2f vec) override;
    void attack();
    void update();
    virtual void display(re::Camera camera);
    void go_to(re::Point2f finish_point);

    re::AnimationPtr movingAnim_Forward; // moving animation
    re::ResourceManager resource_manager;
};

