#pragma once

#include <RealEngine/graphic/animation.h>
#include <cmath>
#include <iostream>
#include <RealEngine/physic_core.h>
#include "RealEngine/event.h"
#include "events/move_event.h"
#include "events/attack_event.h"
#include <chrono>

#include "physgameobject.h"

enum class Action { IDLE, MOVING, ATTACKING };
enum class Side { BRIGHT, DARK };

class Unit 
    : public PhysGameObject
    , public re::EventSubscriber
{
public:

    Unit(re::Point2f pos, std::vector<std::vector<int>> &new_map);
     Unit(re::Point2f pos);
    ~Unit(){}
    double get_hp();
    virtual void attack(int target_id);
    virtual void update();
    virtual void display(re::Camera camera);
    void dealDamage(int damage);
    void onDeath();
    void setAction(Action action) { cur_action = action; };
    void setUnitsArray(std::vector<std::shared_ptr<Unit>> *units) { this->units = units; };

    void move_unit();
    void set_new_way(re::Point2f finish);
    void on_event(std::shared_ptr<re::Event> event);
    void update_way();
    unsigned int get_index();
    void update_index();
    re::Point2f get_cell(int index);
    // from Physic Engine
    virtual void onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) override;

    Side side = Side::BRIGHT;
protected:
    void go_to(re::Point2f finish_point);
    void attack_event();

protected:
    std::vector<std::shared_ptr<Unit>> *units;
    std::vector <re::Point2f> way; // WTF?
    int index; // index of what?
    int hp, maxhp;
    float attack_per_second = 1.0;
    int target_id = 0;
    int movespeed = 130;
    int attack_range = 200;
    int damage = 50;
    std::chrono::steady_clock::time_point last_attack_time;
    re::Point2f goto_point = re::Point2f();
    Action cur_action = Action::IDLE;
    std::vector<std::vector<int>> map;

    re::Point2f fireball_pos;
    bool fireball_alive = false;

    void draw_fireball(re::Camera camera);
};

