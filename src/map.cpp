#include "map.h"

#include "RealEngine/math.h"

Map::Map()
{

}

Map::Map( re::Game &world, std::string path )
{
    map = (re::parse_tiled( re::parse_xml( path ) ))[0];

    for (auto objectData : map.objectgroup[0].group)
    {
        std::shared_ptr<DrawableGameObject> dobj = std::make_shared<DrawableGameObject>(re::Point2f(objectData.x, objectData.y));
        if (!objectData.poly.points.empty()){
            for (auto vertex : objectData.poly.points)
                dobj->addPoint(re::Vector2f(vertex.x, vertex.y));
            for (int i = 0; i < objectData.poly.points.size() - 1; i++)
                dobj->addEdge(i, i + 1);
            dobj->addEdge(objectData.poly.points.size() - 1, 0);
            re::GameObjectPtr obj = dobj;
            world.addObject(obj);
        }
        objects.push_back( dobj );
    }
}

void Map::draw( re::Camera camera )
{
    for( auto object : objects )
    {
        object->display( camera );
    }
}