#pragma once

#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>
#include "../map.h"

class GameLogic : public re::EventSubscriber
{
public:
    GameLogic();
    virtual void on_event(std::shared_ptr<re::Event> event);
    void update();
    void draw( re::Camera );
    re::Game world;

    Map map;

};