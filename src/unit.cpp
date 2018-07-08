#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include "unit.h"
#include <iostream>

Unit::Unit(re::Point2f pos) 
    : PhysGameObject(pos) 
{
    hp = 500;
    maxhp = 500;

    addPoint(re::Point2f(-5, -5));
    addPoint(re::Point2f(-5, 5));
    addPoint(re::Point2f(5, 5));
    addPoint(re::Point2f(5, -5));
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0);
    setRigidbodySimulated(true);
    setFriction(1.0);
    setBounciness(0.0);
}


void Unit::update(){
    if (getPosition().distance_to(goto_point) < 20)
        setVelocity(re::Point2f(0,0));
}


void Unit::display(re::Camera camera){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f screen_pos = camera.world_to_screen(geo_pos); 

    float size = camera.meter_to_screen(50);
    re::draw_rectangle(screen_pos - re::Point2f(size,size), re::Point2f(size,size), re::GREEN);

    if (re::ConfigManager::get_property("common/debug_display") == "1"){
        re::Point2f screen_pos = camera.world_to_screen(goto_point);
        re::draw_rectangle(screen_pos, re::Point2f(size, size), re::RED);
    }
}

void Unit::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}

void Unit::go_to(re::Point2f finish_point){
    setVelocity((finish_point - getPosition()).Normalized() * 130);
    goto_point = finish_point;
}
