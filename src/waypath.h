#pragma once

#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include <iostream>

class Waypath
{
public:
    void addWaypoint(re::Point2f point)
    {
        waypoints.push_back(point);
    }
    re::Point2f* next()
    {
        int count = waypoints.size();
        if (count == 1)
            return &(waypoints[0]);
        if (count == 0)
            return nullptr;
        current_point += direction;
        if (isRepeating)
        {
            if (current_point < 0)
            {
                if (isCycle)
                {
                    current_point = count - 1;
                }
                else
                {
                    direction = 1;
                    current_point = 1;
                }
            }
            if (current_point >= count)
            {
                if (isCycle)
                {
                    current_point = 0;
                }
                else
                {
                    direction = -1;
                    current_point = count - 2;
                }
            }
        }
        else
        {
            if (current_point >= count)
                return nullptr;
        }
        return &(waypoints[current_point]);
    }
    re::Point2f current()
    {
        return waypoints[current_point == -1 ? 0 : current_point];
    }
    void reverse()
    {
        std::reverse(waypoints.begin(), waypoints.end());
    }
    bool isRepeating = false;
    bool isCycle = true;
private:
    std::vector<re::Point2f> waypoints;
    int current_point = -1;
    int direction = 1;
};