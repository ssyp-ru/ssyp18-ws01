#include <iostream>
#include "gamelogic.h"
#include <RealEngine/physic_core.h>

#include "../physgameobject.h"

GameLogic::GameLogic() {
    this->map = Map( world, "map.tmx" );
    obstacles = Generate_obstacles(50, 100, 100, world);
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    
}

void GameLogic::update() {
    world.updateTick();
}

void GameLogic::draw( re::Camera camera ) {
    map.draw(camera);
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<PhysGameObject,re::PhysicObject>( object );
        drawable_object->display( camera );
    }
    /*for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if (obstacles[i][j] == 1){
                re::draw_rectangle(j * 5, i * 5, 5, 5, re::Color(255, 0, 0));
            }
        }
    }*/
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

    if( target.first != -1 ) {
        ((PhysGameObject *)target.second)->setPosition( 
            ((PhysGameObject *)target.second)->getPosition() + 
            re::Point2f(0,10) );
    }
}