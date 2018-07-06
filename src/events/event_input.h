#include <RealEngine/event.h>
#include <RealEngine/math.h>

enum event_input
{
    mouse
};

class InputEventMouse : public re::Event
{
public:
    InputEventMouse(unsigned int event_category, unsigned int event_type);
    virtual std::vector<char> serialize();
    virtual void deserialize( std::vector<char> );

    re::Point2f pos;
    int button;
};