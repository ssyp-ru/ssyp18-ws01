#include "gamelogic.h"
#include "../events/event_enum.h"
#include "../events/event_input.h"
#include <RealEngine/physic_core.h>

#include "../drawable_game_object.h"

GameLogic::GameLogic()
{
    this->map = Map( world, "map.tmx" );
}

void GameLogic::on_event(std::shared_ptr<re::Event> event)
{
    if( event->get_category() == event_category::input )
    {
        if( event->get_type() == event_input::mouse )
        {
            InputEventMouse *mouse_input = (InputEventMouse*)event.get();
            std::shared_ptr<DrawableGameObject> dobj = std::make_shared<DrawableGameObject>(re::Point2f(mouse_input->pos.x, mouse_input->pos.y));
            dobj->addPoint(re::Vector2f(10,10));
            dobj->addPoint(re::Vector2f(10,-10));
            dobj->addPoint(re::Vector2f(-10,-10));
            dobj->addPoint(re::Vector2f(-10,10));
            dobj->addEdge(0,1);
            dobj->addEdge(1,2);
            dobj->addEdge(2,3);
            dobj->addEdge(0,3);
            re::GameObjectPtr obj = dobj;
            this->world.addObject(obj);
            /*if (!objectData.poly.points.empty()){
                for (auto vertex : objectData.poly.points)
                    dobj->addPoint(re::Vector2f(vertex.x, vertex.y));
                for (size_t i = 0; i < objectData.poly.points.size() - 1; i++)
                    dobj->addEdge(i, i + 1);
                dobj->addEdge(objectData.poly.points.size() - 1, 0);
                re::GameObjectPtr obj = dobj;
                world.addObject(obj);
            }
            objects.push_back( dobj );*/
        }
    }
}

void GameLogic::update()
{
    
}

void GameLogic::draw( re::Camera camera )
{
    map.draw(camera);
    for( auto object : this->world.getWorld() )
    {
        auto drawable_object = std::static_pointer_cast<DrawableGameObject,re::GameObject>( object );
        drawable_object->display( camera );
    }
}