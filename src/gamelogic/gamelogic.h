#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include <RealEngine/camera.h>
#include "../map.h"
#include "../obstacles_generator.h"

class GameLogic : public re::EventSubscriber
{
public:
    std::vector<std::vector<int>> obstacles;
    GameLogic();
    virtual void on_event(std::shared_ptr<re::Event> event);
    void update();
    void draw( re::Camera );
    re::PhysicWorld world;

    Map map;

};