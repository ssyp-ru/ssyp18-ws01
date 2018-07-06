#include "event_input.h"

InputEventMouse::InputEventMouse(unsigned int event_category, unsigned int event_type) : re::Event(event_category,event_type) {}

std::vector<char> InputEventMouse::serialize()
{
    std::vector<char> msg;
    msg.push_back(0);
    msg.push_back(0);
    msg.push_back( (unsigned char)(this->pos.x) );
    msg.push_back( int(this->pos.x) / 256 );

    msg.push_back( (unsigned char)(this->pos.y) );
    msg.push_back( int(this->pos.y) / 256 );

    msg.push_back( this->button );
    return msg;
}

void InputEventMouse::deserialize( std::vector<char> msg )
{
    this->pos.x = (unsigned char)msg[2];
    this->pos.x += msg[3] * 256;

    this->pos.y = (unsigned char)msg[4];
    this->pos.y += msg[5] * 256;

    this->button = msg[6];
}