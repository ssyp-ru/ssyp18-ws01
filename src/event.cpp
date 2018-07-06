#include "event.h"
#include "events/event_enum.h"
#include "events/event_input.h"

void deserealize( std::vector<char> msg )
{
    switch( msg[0] )
    {
    case event_category::input:
        switch( msg[1] )
        { 
        case event_input::mouse:
            std::shared_ptr<InputEventMouse> mouse_input = std::make_shared<InputEventMouse>( uint(msg[0]), uint(msg[1]) );
            mouse_input->deserialize(msg);
            mouse_input->set_shared(false);
            re::publish_event(mouse_input);
            break;
        }
    }
}

void EventSerealizerServer::on_event(std::shared_ptr<re::Event> event)
{
    if( !event->is_shared() )
    {
        return;
    }
    std::vector<char> msg = event->serialize();
    msg[0] = event->get_category();
    msg[1] = event->get_type();
    for( int i = 0; i < tcp_server->get_client_count(); i++ )
    {
        tcp_server->send( i, msg );
    }
}

EventSerealizerServer::EventSerealizerServer( re::TCPServerPtr server )
{
    this->tcp_server = server;
}

void EventSerealizerServer::deserealize_server( int id, std::vector<char> msg )
{
    for( int i = 0; i < tcp_server->get_client_count(); i++ )
    {
        if( i != id )
        {
            tcp_server->send( i, msg );
        }
    }

    deserealize(msg);
}

EventSerealizerClient::EventSerealizerClient( re::TCPClientPtr client )
{
    this->tcp_client = client;
    client->set_recive_callback( std::bind( &EventSerealizerClient::deserealize_client,
                                            this,
                                            std::placeholders::_1 ) );
}

void EventSerealizerClient::on_event(std::shared_ptr<re::Event> event)
{
    if( !event->is_shared() )
    {
        return;
    }

    std::vector<char> msg;
    msg = event->serialize();
    msg[0] = event->get_category();
    msg[1] = event->get_type();
    tcp_client->send( msg );
}

void EventSerealizerClient::deserealize_client( std::vector<char> msg )
{
    deserealize( msg );
}