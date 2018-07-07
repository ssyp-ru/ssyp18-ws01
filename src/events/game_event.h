#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

#include "lobby_event.h"

const int GAME_EVENT_CATEGORY = 4;

enum class GameEventType {
    GAME_START
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
};