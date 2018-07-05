#include "drawable_game_object.h"

DrawableGameObject::DrawableGameObject( re::Point2f pos ) 
    : re::GameObject::GameObject( re::Vector2f(pos.x,pos.y))
{

}

void DrawableGameObject::display( re::Camera camera )
{
    re::Point2f pos = re::Point2f( this->position.X, this->position.Y );
    for (auto curEdge : *getEdges())
    {
        re::draw_line(
            // camera.world_to_screen( re::Point2f( curEdge.P1->X, curEdge.P1->X ) ),
            // camera.world_to_screen( re::Point2f( curEdge.P2->X, curEdge.P2->X ) ),
            camera.world_to_screen( pos + re::Point2f( curEdge.P1->X, curEdge.P1->Y )),
            camera.world_to_screen( pos + re::Point2f( curEdge.P2->X, curEdge.P2->Y )),
            re::BLACK );
    }
}