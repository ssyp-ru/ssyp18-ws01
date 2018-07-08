#include <iostream>
#include "gamelogic.h"
#include <RealEngine/physic_core.h>
//#include <fstream>
#include "../obstacles_generator.h"

GameLogic::GameLogic()
{
    this->map = Map( world, "map.tmx" );
    obstacles = generate_obstacles(50, 100, 100, world);
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    
}

void GameLogic::update()
{
    world.updateTick();
}

void GameLogic::draw( re::Camera camera )
{
    //ofstream fout;
   // fout.open("map.txt");
    map.draw(camera);
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<DrawableGameObject,re::PhysicObject>( object );
        drawable_object->display( camera );
    }
    for (size_t i = 0; i < obstacles.size(); i++){
        for (size_t j = 0; j < obstacles.size(); j++){
            if (obstacles[i][j] == 1){
               // fout << obstacles[i][j];
                re::draw_rectangle(j * 2, i * 2, 2, 2, re::Color(0, 0, 0));
            }
            else{
                //fout << obstacles[i][j];
            }
        }
       // fout << std::endl;
    }
    //fout.close();
}