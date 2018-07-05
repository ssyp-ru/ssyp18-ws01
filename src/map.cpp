#include "map.h"

Map::Map()
{
    
}

Map::Map( std::string path )
{
    map = (re::parse_tiled( re::parse_xml( path ) ))[0];
}