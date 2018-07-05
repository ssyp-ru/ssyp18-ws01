#pragma once

#include <RealEngine/tiled_parser.h>
#include <RealEngine/camera.h>

#include "drawable_game_object.h"

class Map
{
public:
    Map();
    Map( re::Game &world,std::string path );
    void draw( re::Camera camera );

    std::vector<std::shared_ptr<DrawableGameObject>> objects;
private:
    re::Map map;
};