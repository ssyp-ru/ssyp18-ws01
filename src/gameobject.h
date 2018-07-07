#pragma once

#include <RealEngine/physic_core.h>
#include <RealEngine/math.h>
#include <RealEngine/camera.h>
#include <RealEngine/graphic.h>

class GameObject : public re::GameObject {
public:
    GameObject( re::Point2f pos, int object_id );

    virtual void display(re::Camera camera) {
        re::Point2f pos = re::Point2f( this->position.X, this->position.Y );
        for (auto curEdge : *getEdges()) {
            re::draw_line(
                camera.world_to_screen( pos + re::Point2f( curEdge.P1->X, curEdge.P1->Y )),
                camera.world_to_screen( pos + re::Point2f( curEdge.P2->X, curEdge.P2->Y )),
                re::BLACK );
        }
    }

    int get_id() {
        return this->object_id_;
    }
private:
    int object_id_;
};