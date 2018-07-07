#pragma once

#include <RealEngine/event.h>

#include <vector>
#include "../events/lobby_event.h"
#include "../events/network_event.h"

class Lobby : public re::EventSubscriber {
public:

    bool is_server = false;

    int get_players_count() const {
        return members.size();
    }

    LobbyMember get_player( size_t id ) const {
        return members[id];
    }

    virtual void on_event(std::shared_ptr<re::Event> event) {
        bool need_sync = false;
        switch( event->get_category() )
        {
        case LOBBY_EVENT_CATEGORY:
            switch( event->get_type() )
            {
                case int(LobbyEventType::LOBBY_SYNC) :
                    members = std::dynamic_pointer_cast<LobbySyncEvent,re::Event>(event)->members_;
                    break;
                case int(LobbyEventType::LOBBY_JOIN) :
                {
                    if(!is_server)
                    {
                        return;
                    }
                    std::string name = std::dynamic_pointer_cast<LobbyJoinEvent,re::Event>(event)->name_;
                    members[members.size()-1].name = name;
                    need_sync = true;
                    break;
                }
            }
            break;
        case NETWORK_EVENT_CATEGORY:
            switch( event->get_type() )
            {
                case int(NetworkEventType::DISCONNECT):
                {
                    size_t sock_id = std::dynamic_pointer_cast<NetworkDisconnectionEvent,re::Event>(event)->sock_id_;
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
                case int(NetworkEventType::CONNECT):
                {
                    LobbyMember new_member;
                    new_member.name = "asd";
                    new_member.sock_id = std::dynamic_pointer_cast<NetworkConnectionEvent,re::Event>(event)->sock_id_;
                    new_member.player_id = members.size();
                    members.push_back( new_member );
                    break;
                }
            }
        }

        if( need_sync ) {
            auto sync_event = std::make_shared<LobbySyncEvent>( this->members );
            sync_event->set_shared( true );
            re::publish_event( sync_event );
        }
    }

    std::vector<LobbyMember> members;
};