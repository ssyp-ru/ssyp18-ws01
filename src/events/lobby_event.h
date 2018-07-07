#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int LOBBY_EVENT_CATEGORY = 3;

enum class LobbyEventType {
    LOBBY_SYNC,
    LOBBY_JOIN
};

struct LobbyMember
{
    std::string name;
    unsigned int sock_id;
    int player_id;
};

class LobbySyncEvent : public re::Event {
public:
    LobbySyncEvent(std::vector<LobbyMember> members)
        : Event(LOBBY_EVENT_CATEGORY, (int)LobbyEventType::LOBBY_SYNC)
        , members_(members)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        
        j["user_count"] = this->members_.size();

        for( size_t i = 0; i < members_.size(); i++ )
        {
            j[i]["name"] = members_[i].name;
            j[i]["player_id"] = members_[i].player_id;
        }

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        size_t member_count = j["user_count"];

        for( size_t i = 0; i < member_count; i++ )
        {
            LobbyMember lobby_member;
            lobby_member.name = j[i]["name"];
            lobby_member.player_id = j[i]["player_id"];
            members_.push_back( lobby_member );
        }
    }

    std::vector<LobbyMember> members_;
};

class LobbyJoinEvent : public re::Event {
public:
    LobbyJoinEvent(std::string name)
        : Event(LOBBY_EVENT_CATEGORY, (int)LobbyEventType::LOBBY_JOIN)
        , name_(name)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        
        j["name"] = this->name_;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        name_ = j["name"];
    }

    std::string name_;
};