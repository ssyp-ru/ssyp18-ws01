#include "drawable_game_object.h"

DrawableGameObject::DrawableGameObject( re::Point2f pos ) 
    : re::PhysicObject::PhysicObject( re::Point2f(pos.x,pos.y))
{

}

void DrawableGameObject::display( re::Camera camera )
{
    re::Point2f pos = re::Point2f( this->position.x, this->position.y );
    for (auto curEdge : *getEdges())
    {
        re::draw_line(
            // camera.world_to_screen( re::Point2f( curEdge.P1->X, curEdge.P1->X ) ),
            // camera.world_to_screen( re::Point2f( curEdge.P2->X, curEdge.P2->X ) ),
            camera.world_to_screen( pos + re::Point2f( curEdge.P1->x, curEdge.P1->y )),
            camera.world_to_screen( pos + re::Point2f( curEdge.P2->x, curEdge.P2->y )),
            re::BLACK );
    }
}