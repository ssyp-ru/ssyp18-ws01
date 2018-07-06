#include <RealEngine/event.h>
#include <RealEngine/physic_core.h>
#include "../map.h"

class GameLogic : public re::EventSubscriber
{
public:
    virtual void on_event(std::shared_ptr<re::Event> event);
    void update();
    re::Game world;

    Map map;

};