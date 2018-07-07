#pragma once

#include "map.h"
#include <RealEngine/physic_core.h>
#include <vector>

static std::vector<std::vector<int>> Generate_obstacles (float cell_size, int counter_X, int counter_Y, re::PhysicWorld &world){
    bool free;
    std::vector<std::vector<int>> map_vector;
    std::vector<re::PhysicObjectPtr> obj = world.getWorld();
    for (int i = 0; i < counter_X; i++){
        map_vector.push_back(std::vector<int>());
        for (int j = 0; j < counter_Y; j++){                
            free = true;
            re::PhysicObjectPtr ptrobj = std::make_shared<re::PhysicObject>();
            ptrobj->setPosition(re::Point2f(j * cell_size, i * cell_size));
            ptrobj->addPoint(re::Point2f(cell_size, 0)); // 0
            ptrobj->addPoint(re::Point2f(cell_size, cell_size)); // 1
            ptrobj->addPoint(re::Point2f(0, cell_size)); // 2
            ptrobj->addPoint(re::Point2f(0, 0)); // 2
            ptrobj->addEdge(0, 1);
            ptrobj->addEdge(1, 2);
            ptrobj->addEdge(2, 3);
            ptrobj->addEdge(0, 3);

            for (size_t k = 0; k < obj.size(); k++){
                if (ptrobj->needTestWith(*(obj[k])))
                {
                    if (ptrobj->removeCollisionWith(*(obj[k])).length() > 1e-6){
                        map_vector[i].push_back(1);
                        std::cout << '1' << std::flush;
                        free = false;  // 1 is blocked
                        break;
                    }
                }
            }
            if (free) 
            {
                std::cout << '0' << std::flush;
                map_vector[i].push_back(0);
            }
        } 
        std::cout << std::endl;
    }
    return std::vector<std::vector<int>> (map_vector);
}
