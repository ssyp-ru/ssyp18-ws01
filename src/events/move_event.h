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

struct MoveSyncData {
    re::Point2f position;
    re::Point2f velocity;
    int object_id;
};

class MoveSyncEvent : public re::Event {
public:
    MoveSyncEvent(std::vector<MoveSyncData> objects)
        : Event(MOVE_EVENT_CATEGORY, (int)MoveEventType::PLAYER_SYNC)
        , objects(objects)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = MOVE_EVENT_CATEGORY;
        j["type"] = (int)MoveEventType::PLAYER_SYNC;
        j["object_count"] = this->objects.size();
        for( size_t i = 0; i < objects.size(); i++ ) {
            j[std::to_string(i)]["x"]     = objects[i].position.x;
            j[std::to_string(i)]["y"]     = objects[i].position.y;
            j[std::to_string(i)]["vec_x"] = objects[i].velocity.x;
            j[std::to_string(i)]["vec_y"] = objects[i].velocity.y;
            j[std::to_string(i)]["id"]    = objects[i].object_id;
        }

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        size_t object_count = j["object_count"];
        for( size_t i = 0; i < object_count; i++ ) {
            MoveSyncData new_data;
            new_data.position.x = j[std::to_string(i)]["x"];
            new_data.position.y = j[std::to_string(i)]["y"];
            new_data.velocity.x = j[std::to_string(i)]["vec_x"];
            new_data.velocity.y = j[std::to_string(i)]["vec_y"];
            new_data.object_id  = j[std::to_string(i)]["id"];
        }
    }

    std::vector<MoveSyncData> objects;
};