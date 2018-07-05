#include "event.h"

void deserealize( std::vector<char> msg )
{
    std::shared_ptr<re::Event> event;
    switch( msg[0] )
    {
        
    }
    re::publish_event( event );
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
    std::vector<char> msg;
    msg = event->serialize();
    tcp_client->send( msg );
}

void EventSerealizerClient::deserealize_client( std::vector<char> msg )
{
    deserealize( msg );
}