#include "gamelogic.h"
#include "../events/event_enum.h"
#include <RealEngine/physic_core.h>

#include "../drawable_game_object.h"

GameLogic::GameLogic()
{
    this->map = Map( world, "map.tmx" );
}

void GameLogic::on_event(std::shared_ptr<re::Event> event)
{
    
}

void GameLogic::update()
{
    
}

void GameLogic::draw( re::Camera camera )
{
    map.draw(camera);
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<DrawableGameObject,re::GameObject>( object );
        drawable_object->display( camera );
    }
}