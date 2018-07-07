#pragma once

#include <RealEngine/tiled_parser.h>
#include <RealEngine/camera.h>

#include "drawable_game_object.h"

class Map
{
public:
    Map();
    Map(re::PhysicWorld &world, std::string path);
    void draw(re::Camera camera);

    static const int16_t PLATFORM_PHYSIC_TYPE = 0b01; 
private:
    re::Map map;
    re::ImagePtr backgroung;
};