#include "event.h"
#include "events/move_event.h"
#include "events/lobby_event.h"
#include <json.hpp>

void deserealize( std::vector<char> msg )
{
    std::string raw_json( msg.data(), msg.size() );
    nlohmann::json j = nlohmann::json::parse(raw_json);
    switch( int(j["category"]) )
    {
    case MOVE_EVENT_CATEGORY:
        switch( int(j["type"]) )
        { 
            case int(MoveEventType::PLAYER_MOVE) :
            {
                std::shared_ptr<MoveEvent> move_input = std::make_shared<MoveEvent>(0,re::Point2f());
                move_input->deserialize(msg);
                re::publish_event( move_input );
                break;
            }
        }
        break;
    case LOBBY_EVENT_CATEGORY:
        switch( int(j["type"]) )
        {
            case int(LobbyEventType::LOBBY_JOIN):
            {
                auto move_input = std::make_shared<LobbyJoinEvent>("");
                move_input->deserialize(msg);
                re::publish_event( move_input );
                break;
            }
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
    tcp_client->send( msg );
}

void EventSerealizerClient::deserealize_client( std::vector<char> msg )
{
    deserealize( msg );
}