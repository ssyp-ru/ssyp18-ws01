#pragma once

#include <chrono>

#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>
#include "../map.h"

#include "../player.h"

const int CREEP_RESPAWN_TIME_MS = 40'000;

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
    void spawn_creep();

    re::PhysicWorld world;
    Map map;

    std::vector<std::shared_ptr<Unit>> units;
    int self_player_id;
    Side self_side;
    bool is_server;
    bool player_spawned_once = false;

    std::chrono::time_point<std::chrono::steady_clock> last_sync_time, last_creep_spawn_time;
};