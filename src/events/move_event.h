#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int MOVE_EVENT_CATEGORY = 1;

enum class MoveEventType {
    PLAYER_MOVE,
    PLAYER_SYNC
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
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        j["x"] = this->finish_point.x;
        j["y"] = this->finish_point.y;
        j["id"] = this->player_id;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        finish_point.x = j["x"];
        finish_point.y = j["y"];
        player_id = j["id"];
    }

    re::Point2f finish_point;
    int player_id;
};

class MoveSyncEvent : public re::Event {
public:
    MoveSyncEvent(int _player_id, re::Point2f pos, re::Point2f vec)
        : Event(MOVE_EVENT_CATEGORY, (int)MoveEventType::PLAYER_SYNC)
        , pos(pos)
        , vec(vec)
        , player_id(_player_id)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        j["x"] = this->pos.x;
        j["y"] = this->pos.y;
        j["vec_x"] = this->vec.x;
        j["vec_y"] = this->vec.y;
        j["id"] = this->player_id;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        pos.x = j["x"];
        pos.y = j["y"];
        vec.x = j["vec_x"];
        vec.y = j["vec_y"];
        player_id = j["id"];
    }

    re::Point2f pos;
    re::Point2f vec;
    int player_id;
};