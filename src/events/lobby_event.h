#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int LOBBY_EVENT_CATEGORY = 3;

enum class LobbyEventType {
    LOBBY_SYNC,
    LOBBY_JOIN
};

struct LobbyMember {
    std::string name;
    unsigned int sock_id;
    int team;
    int player_id;
};

class LobbySyncEvent : public re::Event {
public:
    LobbySyncEvent(std::vector<LobbyMember> members)
        : Event(LOBBY_EVENT_CATEGORY, (int)LobbyEventType::LOBBY_SYNC)
        , members(members)
    {}

    std::vector<char> serialize() {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        
        j["user_count"] = this->members.size();

        for( size_t i = 0; i < members.size(); i++ )
        {
            j[std::to_string(i)]["name"] = members[i].name;
            j[std::to_string(i)]["player_id"] = members[i].player_id;
            j[std::to_string(i)]["team"] = members[i].team;
        }

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg ) {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        size_t member_count = j["user_count"];

        for( size_t i = 0; i < member_count; i++ ) {
            LobbyMember lobby_member;
            lobby_member.name = j[std::to_string(i)]["name"];
            lobby_member.player_id = j[std::to_string(i)]["player_id"];
            lobby_member.team = j[std::to_string(i)]["team"];
            members.push_back( lobby_member );
        }
    }

    std::vector<LobbyMember> members;
};

class LobbyJoinEvent : public re::Event {
public:
    LobbyJoinEvent(std::string name, int team, int id)
        : Event(LOBBY_EVENT_CATEGORY, (int)LobbyEventType::LOBBY_JOIN)
        , name(name)
        , team(team)
        , id(id)
    {}

    std::vector<char> serialize() {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        
        j["team"] = this->team;
        j["name"] = this->name;
        j["id"] = this->id;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg ) {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        name = j["name"];
        team = j["team"];
        id = j["id"];
    }

    std::string name;
    int team;
    int id;
};