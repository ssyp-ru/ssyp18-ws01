#include <iostream>
#include "gamelogic.h"
#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include <fstream>
#include <chrono>

using namespace std;

#include "../events/move_event.h"
#include "../events/game_event.h"
#include "../physgameobject.h"

const int sync_time = 100'000;

GameLogic::GameLogic() {
    this->map = Map( world, "map.tmx" );
    last_sync_time = std::chrono::steady_clock::now();   
    this->is_server = false;
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    switch( event->get_category() )
    {
    case GAME_EVENT_CATEGORY:
        switch( event->get_type() ) {
            case int(GameEventType::PLAYERS_JOIN):
            {
                auto join_event = std::dynamic_pointer_cast<GamePlayersJoinEvent,re::Event>( event );
                
                auto player = std::make_shared<Player>( re::Point2f(330, 4690));
                this->players.push_back(player);
                world.addObject(player);
                if( join_event->is_local ) {
                    self_player_id = player->get_id();
                }
                break;
            }
            case int(GameEventType::GAME_HOST):
            {
                this->is_server = true;
                break;
            }
        }
        break;
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
                    player->setPosition( sync_event->objects[i].position );
                    player->setVelocity( sync_event->objects[i].velocity );
                }
            }
        }
    }
}

void GameLogic::update() {
    world.updateTick();

    int time_milils = (std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::steady_clock::now() - last_sync_time)).count();
    if (is_server && time_milils > sync_time){
        last_sync_time = std::chrono::steady_clock::now();   
        std::vector<MoveSyncData> move_sync_data;
        for( auto player : players ) {
            MoveSyncData data;
            data.position = player->getPosition();
            data.velocity = player->getVelocity();
            data.object_id = player->get_id();
            move_sync_data.push_back( data );
        }
        auto sync_event = std::make_shared<MoveSyncEvent>( move_sync_data );
        sync_event->set_shared(true);
        re::publish_event(sync_event);
    }

    for (auto& player: players) {
        player->update();
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

    for( auto player : players )
    {
        player->display( camera );
    }

    if (re::ConfigManager::get_property("common/debug_display") == "1"){
        world.debug_display(camera);
    }
}

void GameLogic::click( re::Point2f pos ) {
    std::pair<int,GameObject*> target;
    target.first = -1;
    for( auto object : GameObject::object_map) {
        PhysGameObject * phys_object = dynamic_cast<PhysGameObject*>( object.second );
        if( phys_object && phys_object->isPointInside( pos ) ) {
            target = object;
            break; 
        }
    }

    if (target.first == -1)
    {
        auto move_event = std::make_shared<MoveEvent>(this->self_player_id, pos);
        move_event->set_shared(true);
        re::publish_event(move_event);
    } else {
        Unit* unitObj = dynamic_cast<Unit*>(target.second);
        if (unitObj)
        {
            dynamic_cast<Player*>(GameObject::get_object_by_id(this->self_player_id))->attack(target.first);
        }
    }
}