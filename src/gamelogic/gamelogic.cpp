#include <iostream>
#include "gamelogic.h"
#include <RealEngine/physic_core.h>
#include <fstream>

using namespace std;

#include "../events/move_event.h"
#include "../events/game_event.h"
#include "../physgameobject.h"

GameLogic::GameLogic() {
    this->map = Map( world, "map.tmx" );
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    switch( event->get_category() )
    {
    case GAME_EVENT_CATEGORY:
        switch( event->get_type() )
        {
            case int(GameEventType::PLAYERS_JOIN):
            {
                auto join_event = std::dynamic_pointer_cast<GamePlayersJoinEvent,re::Event>( event );
                
                auto player = std::make_shared<Player>( re::Point2f(400,2200));
                this->players.push_back(player);
                world.addObject(player);
                break;
            }
        }
    }
}

void GameLogic::update() {
    world.updateTick();
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

    auto move_event = std::make_shared<MoveEvent>(0, pos);
    move_event->set_shared(true);
    re::publish_event(move_event);
}