#pragma once

#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>
#include "../map.h"
#include "../obstacles_generator.h"

class GameLogic : public re::EventSubscriber
{
public:
    GameLogic();
    virtual void on_event(re::EventPtr event);
    void update();
    void draw( re::Camera );

    void click( re::Point2f pos );
public:    
    std::vector<std::vector<int>> obstacles;
    re::PhysicWorld world;

    Map map;

};