#pragma once

#include <RealEngine/tiled_parser.h>

class Map
{
public:
    Map();
    Map( std::string path );
    void draw();

private:
    re::Map map;
};