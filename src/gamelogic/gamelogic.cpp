#include <iostream>
#include "gamelogic.h"
#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include <fstream>
#include <chrono>
#include "../obstacles_generator.h"
using namespace std;

#include "../events/move_event.h"
#include "../events/spawn_event.h"
#include "../events/game_event.h"
#include "../events/attack_event.h"
#include "../events/creeps_spawn_event.h"
#include "../physgameobject.h"
#include "../creep.h"

const int sync_time = 100'000;

GameLogic::GameLogic() {
    this->map = Map( world, "map.tmx" );
    last_sync_time = std::chrono::steady_clock::now();  
    obstacles = generate_obstacles (20, 250, 250, world);
    this->is_server = false;
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    switch( event->get_category() )
    {
        case CREEPS_SPAWN_EVENT_CATEGORY:
        {
            int midCreepsCount = 1;
            int topCreepsCount = 1;
            int botCreepsCount = 1;
            for (int i = 0; i < topCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(500, 4500), Side::BRIGHT, Line::TOP);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            for (int i = 0; i < midCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(500, 4500), Side::BRIGHT, Line::MID);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            for (int i = 0; i < botCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(500, 4500), Side::BRIGHT, Line::BOT);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            for (int i = 0; i < topCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(4500, 500), Side::DARK, Line::TOP);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            for (int i = 0; i < midCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(4500, 500), Side::DARK, Line::MID);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            for (int i = 0; i < botCreepsCount; i++)
            {
                auto creep = std::make_shared<Creep>(re::Point2f(4500, 500), Side::DARK, Line::BOT);
                creep->setUnitsArray(&units);
                this->units.push_back(creep);
                world.addObject(creep);
            }
            return;
        }
        case GAME_EVENT_CATEGORY:
            switch( event->get_type() ) {
                case int(GameEventType::PLAYERS_JOIN):
                {
                    auto join_event = std::dynamic_pointer_cast<GamePlayersJoinEvent,re::Event>( event );
                    
                    auto player = std::make_shared<Player>( re::Point2f(340, 4680), obstacles);
                    this->units.push_back(player);
                    world.addObject(player);
                    if( join_event->is_local ) {
                    auto creepsSpawn = std::make_shared<CreepsSpawnEvent>();
                        self_player_id = player->get_id();
                        std::cout << "throwing creeps spawning event" << std::endl;
                        creepsSpawn->set_shared(true);
                        re::publish_event(creepsSpawn);
                    }
                    break;
                }
                case int(GameEventType::GAME_HOST):
                {
                    this->is_server = true;
                    break;
                }
            }
            return;
        case MOVE_EVENT_CATEGORY:
            switch( event->get_type() ) {
                case int(MoveEventType::PLAYER_SYNC):
                {
                    if( is_server ) {
                        return;
                    }
                    auto sync_event = std::dynamic_pointer_cast<MoveSyncEvent,re::Event>( event );
                    for( size_t i = 0; i < sync_event->objects.size(); i++ ) {
                        PhysGameObject *player = (PhysGameObject*)GameObject::get_object_by_id( sync_event->objects[i].object_id );
                        if ( player != nullptr ) {
                            player->setPosition( sync_event->objects[i].position );
                            player->setVelocity( sync_event->objects[i].velocity );
                        }
                    }
                }
            }
            return;
        case ATTACK_EVENT_CATEGORY: {
            switch(event->get_type()){
                case (int)AttackEventType::PLAYER_DEATH: {
                    auto death_event = std::dynamic_pointer_cast<DeathEvent,re::Event>( event );
                    for (auto iter = units.begin(); iter != units.end(); iter++){
                        if ((*iter)->get_id() == death_event->player_id){
                            world.removeObject(*iter);
                            units.erase(iter);
                            GameObject::object_map[death_event->player_id] = nullptr;
                            return;
                        }
                    }
                    return;
                }
                case (int)AttackEventType::PLAYER_ATTACK :
                {
                    auto attack_event = std::dynamic_pointer_cast<AttackEvent,re::Event>( event );
                    std::cout << attack_event->player_id;
                    Unit* player = (Unit*)GameObject::get_object_by_id( attack_event->player_id );
                    player->attack( attack_event->target_id );
                    return;
                }
            }
            break;
        case SPAWN_EVENT_CATEGORY:
            switch( event->get_type() ) {
                case int( int(SpawnEventType::PLAYER_RESPAWN) ):
                {
                    auto player = std::make_shared<Player>( re::Point2f(330, 4690));
                    this->units.push_back(player);
                    world.addObject(player);
                    if( GameObject::get_object_by_id( self_player_id ) == nullptr ) {
                        this->self_player_id = player->get_id();
                    }
                    return;
                }
            }
        }
    }

}

void GameLogic::update() {
    world.updateTick();

    int time_milils = (std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::steady_clock::now() - last_sync_time)).count();
    if (is_server && (time_milils > sync_time)){
        last_sync_time = std::chrono::steady_clock::now();   
        std::vector<MoveSyncData> move_sync_data;
        for( auto& unit : units ) {
            MoveSyncData data;
            data.position = unit->getPosition();
            data.velocity = unit->getVelocity();
            data.object_id = unit->get_id();
            move_sync_data.push_back( data );
        }
        auto sync_event = std::make_shared<MoveSyncEvent>( move_sync_data );
        sync_event->set_shared(true);
        re::publish_event(sync_event);
    }

    for (auto& unit: units) {
        unit->update();
    }

    if( GameObject::get_object_by_id( self_player_id ) == nullptr ) {
        auto respawn_event = std::make_shared<PlayerRespawnEvent>();
        respawn_event->set_shared( true );
        re::publish_event( respawn_event );            
    }
}

void GameLogic::draw( re::Camera camera )
{
    map.draw(camera);
   
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<PhysGameObject,re::PhysicObject>( object );
        drawable_object->display( camera );
    }

    for( auto& unit : units )
    {
        unit->display( camera );
    }

    if (re::ConfigManager::get_property("common/debug_display") == "1"){
        world.debug_display(camera);
    }
}

void GameLogic::click( re::Point2f pos ) {
    std::pair<int,GameObject*> target(-1, 0);
    //target.first = -1;
    for( auto object : GameObject::object_map) {
        if( object.second == nullptr ) {
            continue;
        }
        PhysGameObject * phys_object = dynamic_cast<PhysGameObject*>( object.second );
        if( phys_object && phys_object->isPointInside( pos ) ) {
            // Work around object with HUGE radius
            if (dynamic_cast<Unit*>( object.second ) != nullptr){
                if (this->self_player_id != target.first){
                    target = object;
                    break;
                }
            }
        }
    }

    if (target.first == -1)
    {
        auto move_event = std::make_shared<MoveEvent>(this->self_player_id, pos);
        move_event->set_shared(true);
        re::publish_event(move_event);
    } else {
        Unit* unitObj = dynamic_cast<Unit*>(target.second);
        if (unitObj) {
            if (this->self_player_id != target.first) {
                auto attack_event = std::make_shared<AttackEvent>(this->self_player_id, target.first);
                attack_event->set_shared(true);
                re::publish_event( attack_event );
            }
        } else {
            auto move_event = std::make_shared<MoveEvent>(this->self_player_id, pos);
            move_event->set_shared(true);
            re::publish_event(move_event);
        }

    }
}