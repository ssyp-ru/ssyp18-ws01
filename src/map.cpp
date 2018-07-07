#include "map.h"

#include "RealEngine/math.h"

Map::Map() {

} 

Map::Map( re::PhysicWorld &world, std::string path )
{
    map = (re::parse_tiled( re::parse_xml( path ) ))[0];

    for (const auto& objectData : map.objectgroup[0].group)
    {
        auto dobj = std::make_shared<DrawableGameObject>(re::Point2f(objectData.x, objectData.y));
        if (!objectData.poly.points.empty()){
            for (auto vertex : objectData.poly.points)
                dobj->addPoint(re::Point2f(vertex.x, vertex.y));
            for (size_t i = 0; i < objectData.poly.points.size() - 1; i++)
                dobj->addEdge(i, i + 1);
            dobj->addEdge(objectData.poly.points.size() - 1, 0);
            re::PhysicObjectPtr obj = dobj;
            world.addObject(obj);
        }
    }
}

void Map::draw( re::Camera camera ) {
    re::Point2f size_background( map.imagelayer[0].width, map.imagelayer[0].height );
    if( !this->backgroung ) {
        this->backgroung = std::make_shared<re::Image>( map.imagelayer[0].img_path );
    }
    re::draw_image_part( re::Point2f(0,0), 
                         camera.world_to_screen(size_background), 
                         re::Point2f(0,0),
                         re::Point2f(1,1),
                         this->backgroung );
    //this->backgroung->getTex();
}