#include "event.h"
#include "events/move_event.h"
#include "events/lobby_event.h"
#include "events/game_event.h"
#include "events/attack_event.h"
#include "events/spawn_event.h"
#include <json.hpp>

void deserealize( std::vector<char> msg ) {
    std::string raw_json( msg.data(), msg.size() );
    nlohmann::json j = nlohmann::json::parse(raw_json);
    switch( int(j["category"]) ) {
    case MOVE_EVENT_CATEGORY:
        switch( int(j["type"]) ) { 
            case int(MoveEventType::PLAYER_MOVE) :
            {
                std::shared_ptr<MoveEvent> move_input = std::make_shared<MoveEvent>(0,re::Point2f());
                move_input->deserialize(msg);
                re::publish_event( move_input );
                break;
            }
            case int(MoveEventType::PLAYER_SYNC) :
            {
                try {
                    auto sync_event = std::make_shared<MoveSyncEvent>( std::vector<MoveSyncData>() );
                    sync_event->deserialize(msg);
                    re::publish_event( sync_event );
                } catch (...) {}
                break;
            }
        }
        break;
    case LOBBY_EVENT_CATEGORY:
        switch( int(j["type"]) ) {
            case int(LobbyEventType::LOBBY_JOIN):
            {
                auto move_input = std::make_shared<LobbyJoinEvent>("",-1,0);
                move_input->deserialize(msg);
                re::publish_event( move_input );
                break;
            }
            case int(LobbyEventType::LOBBY_SYNC):
            {
                auto sync_event = std::make_shared<LobbySyncEvent>( std::vector<LobbyMember>() );
                sync_event->deserialize(msg);
                re::publish_event( sync_event );
                break;
            }
        }
        break;
    case GAME_EVENT_CATEGORY:
        switch( int(j["type"]) ) {
            case int(GameEventType::GAME_START):
            {
                auto start_event = std::make_shared<GameStartEvent>();
                re::publish_event(start_event);
                break;
            }
        }
        break;
    case ATTACK_EVENT_CATEGORY:
        switch( int(j["type"]) ) {
            case int(AttackEventType::PLAYER_ATTACK):
            {
                auto attack_event = std::make_shared<AttackEvent>( 0, 0 );
                attack_event->deserialize( msg );
                re::publish_event( attack_event );
                break;
            }
        }
        break;
    case SPAWN_EVENT_CATEGORY:
        switch( int(j["type"]) ) {
            case int(SpawnEventType::PLAYER_RESPAWN):
            {
                auto spawn_event = std::make_shared<PlayerRespawnEvent>();
                re::publish_event(spawn_event);
                break;
            }
        }
    }
}

void EventSerealizerServer::on_event(std::shared_ptr<re::Event> event) {
    if( !event->is_shared() ) {
        return;
    }
    std::vector<char> msg = event->serialize();
    for( int i = 0; i < tcp_server->get_client_count(); i++ ) {
        tcp_server->send( i, msg );
    }
}

EventSerealizerServer::EventSerealizerServer( re::TCPServerPtr server )
{
    this->tcp_server = server;
}

void EventSerealizerServer::deserealize_server( int id, std::vector<char> msg )
{
    for( int i = 0; i < tcp_server->get_client_count(); i++ ) {
        if( i != id ) {
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

void EventSerealizerClient::on_event(std::shared_ptr<re::Event> event) {
    if( !event->is_shared() ) {
        return;
    }

    std::vector<char> msg;
    msg = event->serialize();
    tcp_client->send( msg );
}

void EventSerealizerClient::deserealize_client( std::vector<char> msg ) {
    deserealize( msg );
}