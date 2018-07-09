#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int CREEPS_SPAWN_EVENT_CATEGORY = 7;

enum class CreepsSpawnEventType {
    NORMAL_CREEPS
};

class CreepsSpawnEvent : public re::Event {
public:
    CreepsSpawnEvent()
        : Event(CREEPS_SPAWN_EVENT_CATEGORY, (int)CreepsSpawnEventType::NORMAL_CREEPS)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
    }

    std::string get_describe_string() { return "CreepsSpawnEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
};