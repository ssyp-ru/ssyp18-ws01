#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

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

    re::Point2f finish_point;
    int player_id;
};