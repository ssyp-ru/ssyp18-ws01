#pragma once

#include "gameobject.h"

class PhysGameObject
    : public GameObject
    , public re::PhysicObject
{
public:
    PhysGameObject( re::Point2f pos )
        : GameObject()
        , re::PhysicObject(pos)
    {

    }

    virtual void display(re::Camera camera) {
        // re::Point2f pos = re::Point2f( this->position.x, this->position.y );
        // for (auto curEdge : *getEdges()) {
        //     re::draw_line(
        //         camera.world_to_screen( pos + re::Point2f( curEdge.P1->x, curEdge.P1->y )),
        //         camera.world_to_screen( pos + re::Point2f( curEdge.P2->x, curEdge.P2->y )),
        //         re::BLACK );
        // }
    }
};