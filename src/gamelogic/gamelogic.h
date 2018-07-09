#pragma once

#include <chrono>

#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>
#include "../map.h"

#include "../player.h"

class GameLogic : public re::EventSubscriber
{
public:
    GameLogic();
    virtual void on_event(re::EventPtr event);
    void update();
    void draw( re::Camera );
    int get_self_id();
    void click( re::Point2f pos );
        std::vector<std::vector<int>> obstacles;
private:    

    re::PhysicWorld world;
    Map map;

    std::vector<std::shared_ptr<Unit>> units;
    int self_player_id;
    bool is_server;
    bool player_spawned_once = false;

    std::chrono::time_point<std::chrono::steady_clock> last_sync_time;
};