#include <RealEngine/event.h>

#include <json.hpp>

const int SPAWN_EVENT_CATEGORY = 7;

enum class SpawnEventType {
    PLAYER_RESPAWN
};

class PlayerRespawnEvent : public re::Event {
public:
    PlayerRespawnEvent()
        : Event(SPAWN_EVENT_CATEGORY, (int)SpawnEventType::PLAYER_RESPAWN)
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

    std::string get_describe_string() { return "PlayerRespawnEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
};
