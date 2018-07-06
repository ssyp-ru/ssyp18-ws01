#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int MOVE_EVENT_CATEGORY = 1;

enum class MoveEventType {
    PLAYER_MOVE
};

class MoveEvent : public re::Event {
public:
    MoveEvent(int _player_id, re::Point2f _finish_point)
        : Event(MOVE_EVENT_CATEGORY, (int)MoveEventType::PLAYER_MOVE)
        , finish_point(_finish_point)
        , player_id(_player_id)
    {}

    std::vector<char> serialize()
    {
        std::vector<char> msg;
        msg.push_back(0);
        msg.push_back(0);
        nlohmann::json j;
        j["x"] = this->finish_point.x;
        j["y"] = this->finish_point.y;
        j["id"] = this->player_id;

        std::string raw_json = j.dump();

        for( size_t i = 0; i < raw_json.size(); i++ )
        {
            msg.push_back( raw_json[i] );
        }

        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json;

        for( size_t i = 2; i < msg.size(); i++ )
        {
            raw_json += msg[i];
        }

        nlohmann::json j = nlohmann::json::parse(raw_json);
        finish_point.x = j["x"];
        finish_point.y = j["y"];
        player_id = j["id"];
    }

    re::Point2f finish_point;
    int player_id;
};