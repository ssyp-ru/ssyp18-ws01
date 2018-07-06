#include "event.h"
#include "events/event_enum.h"
#include "events/move_event.h"

void deserealize( std::vector<char> msg )
{
    switch( msg[0] )
    {
    case MOVE_EVENT_CATEGORY:
        switch( msg[1] )
        { 
        case int(MoveEventType::PLAYER_MOVE) :
            std::shared_ptr<MoveEvent> move_input = std::make_shared<MoveEvent>(0,re::Point2f());
            move_input->deserialize(msg);
            re::publish_event( move_input );
            break;
        }
        break;
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