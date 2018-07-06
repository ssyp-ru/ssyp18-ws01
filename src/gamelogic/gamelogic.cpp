#include <iostream>
#include "gamelogic.h"
#include "../events/event_enum.h"
#include <RealEngine/physic_core.h>

GameLogic::GameLogic()
{
    this->map = Map( world, "map.tmx" );
    obstacles = Generate_obstacles(50, 100, 100, world);
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
        auto drawable_object = std::static_pointer_cast<DrawableGameObject,re::PhysicObject>( object );
        drawable_object->display( camera );
    }
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if (obstacles[i][j] == 1){
                re::draw_rectangle(j * 5, i * 5, 5, 5, re::Color(0, 0, 0));
            }
        }
    }
}