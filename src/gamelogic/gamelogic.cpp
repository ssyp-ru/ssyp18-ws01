#include <iostream>
#include "gamelogic.h"
#include <RealEngine/physic_core.h>
#include <fstream>

using namespace std;

GameLogic::GameLogic()
{
    this->map = Map( world, "map.tmx" );
    obstacles = generate_obstacles(20, 250, 250, world);
}

void GameLogic::on_event(std::shared_ptr<re::Event> event) {
    
}

void GameLogic::update()
{
    world.updateTick();
}

void GameLogic::draw( re::Camera camera )
{
    ofstream fout;
    fout.open("map.txt");
    map.draw(camera);
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<DrawableGameObject,re::PhysicObject>( object );
        drawable_object->display( camera );
    }
    for (int i = 0; i < 250; i++){
        for (int j = 0; j < 250; j++){
            if (obstacles[i][j] == 1){
                fout << obstacles[i][j];
                re::draw_rectangle(j * 2, i * 2, 2, 2, re::Color(0, 0, 0));
            }
            else{
                fout << obstacles[i][j];
            }
        }
        fout << std::endl;
    }
    fout.close();
}