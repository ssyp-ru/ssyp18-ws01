#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

#include "lobby_event.h"

const int GAME_EVENT_CATEGORY = 4;

enum class GameEventType {
    GAME_START,
    PLAYERS_JOIN,
    GAME_HOST
};

class GameStartEvent : public re::Event {
public:
    GameStartEvent()
        : Event(GAME_EVENT_CATEGORY, (int)GameEventType::GAME_START)
    {}

    std::vector<char> serialize() {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        
        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg ) {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
    }

    std::string get_describe_string() { return "GameStartEvent"; }
};

class GamePlayersJoinEvent : public re::Event {
public:
    GamePlayersJoinEvent( LobbyMember player_, bool is_local )
        : Event(GAME_EVENT_CATEGORY, (int)GameEventType::PLAYERS_JOIN)
        //, player(player)
    {
        this->player.name = player_.name;
        this->player.team = player_.team;
        this->is_local = is_local;
    }

    std::string get_describe_string() { return "GamePlayersJoinEvent"; }

    LobbyMember player;
    bool is_local;
};

class GameHostEvent : public re::Event {
public:
    GameHostEvent() 
        : Event(GAME_EVENT_CATEGORY, (int)GameEventType::GAME_HOST)
    {}

    std::string get_describe_string() { return "GameHostEvent"; }
};