#pragma once

#include <RealEngine/event.h>

#include <vector>
#include "../events/lobby_event.h"
#include "../events/network_event.h"
#include "../events/game_event.h"

class Lobby : public re::EventSubscriber {
public:

    Lobby()
    {
        re::subscribe_to_event_category( this, LOBBY_EVENT_CATEGORY );
        re::subscribe_to_event_category( this, NETWORK_EVENT_CATEGORY );
        re::subscribe_to_event_category( this, GAME_EVENT_CATEGORY );
    }

    bool is_server = false;

    int get_self_id()
    {
        return self_id;
    }

    int get_players_count() const {
        return members.size();
    }

    LobbyMember get_player( size_t id ) const {
        return members[id];
    }

    void join( LobbyMember member ) {
        member.player_id = members.size();
        this->members.push_back( member );
    }

    virtual void on_event(std::shared_ptr<re::Event> event) {
        bool need_sync = false;
        switch( event->get_category() ) {
        case LOBBY_EVENT_CATEGORY:
            switch( event->get_type() ) {
                case int(LobbyEventType::LOBBY_SYNC) :
                    if( is_server ) {
                        return;
                    }
                    members = std::dynamic_pointer_cast<LobbySyncEvent,re::Event>(event)->members;
                    if( self_id == 0 ) {
                        self_id = members.size() - 1;
                    }
                    break;
                case int(LobbyEventType::LOBBY_JOIN) :
                {
                    need_sync = true;
                    //if(!is_server) {
                    //    return;
                    //}
                    auto join_event = std::dynamic_pointer_cast<
                                                LobbyJoinEvent,
                                                re::Event>(event);
                    members[join_event->id].name = join_event->name;
                    members[join_event->id].team = join_event->team;
                    need_sync = true;
                    break;
                }
            }
            break;
        case NETWORK_EVENT_CATEGORY:
            switch( event->get_type() )
            {
                case int(NetworkEventType::CLIENT_DISCONNECTED):
                {
                    is_server = true;
                    need_sync = true;
                    auto disconnect_event = std::dynamic_pointer_cast<
                                                    NetworkDisconnectionEvent,
                                                    re::Event>(event);
                    size_t sock_id = disconnect_event->sock_id;
                    for( size_t i = 0; i < members.size(); i++ )
                    {
                        if( members[i].sock_id == sock_id )
                        {
                            members[i] = members[members.size()-1];
                            members.pop_back();
                            break;
                        }
                    }
                    break;
                }
                case int(NetworkEventType::CLIENT_CONNECTED):
                {
                    is_server = true;
                    need_sync = true;
                    LobbyMember new_member;
                    new_member.name = "unnamed";
                    auto connect_event = std::dynamic_pointer_cast<
                                                NetworkConnectionEvent,
                                                re::Event>(event);
                    new_member.sock_id = connect_event->sock_id;
                    new_member.player_id = members.size();
                    members.push_back( new_member );
                    break;
                }
            }
        case GAME_EVENT_CATEGORY:
            switch( event->get_type() )
            {
                case int(GameEventType::GAME_START):
                {
                    for( auto member : members ) {
                        auto join_event = std::make_shared<GamePlayersJoinEvent>(member);
                        join_event->set_shared(false);
                        re::publish_event( join_event );
                    }
                    break;
                }
            }
        }

        if( need_sync && is_server ) {
            auto sync_event = std::make_shared<LobbySyncEvent>( this->members );
            sync_event->set_shared( true );
            re::publish_event( sync_event );
        }
    }

    std::vector<LobbyMember> members;
private:
    int self_id = 0;
};