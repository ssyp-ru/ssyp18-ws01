#pragma once

#include "map.h"
#include <RealEngine/physic_core.h>
#include <vector>
#include <fstream>

static std::vector<std::vector<int>> generate_obstacles (float cell_size, int counter_X, int counter_Y, re::PhysicWorld &world){
    bool free;
//    ofstream cout("map.txt");
    std::vector<std::vector<int>> map_vector;
    std::vector<re::PhysicObjectPtr> obj = world.getWorld();
    for (int i = 0; i < counter_X; i++){
        // std::cout << ".\n";
        map_vector.push_back(std::vector<int>());
        for (int j = 0; j < counter_Y; j++){
            if ((i == 0) || (j == 0) || (i == counter_Y - 1) || (j == counter_X - 1)){
                map_vector[i].push_back(1);
                continue;
            }
 
            free = true;
            re::PhysicObjectPtr ptrobj = std::make_shared<re::PhysicObject>();
            ptrobj->setPosition(re::Point2f(j * cell_size, i * cell_size));
            ptrobj->addPoint(re::Point2f(cell_size, 0)); // 0
            ptrobj->addPoint(re::Point2f(cell_size, cell_size)); // 1
            ptrobj->addPoint(re::Point2f(0, cell_size)); // 2
            ptrobj->addPoint(re::Point2f(0, 0)); // 3
            ptrobj->addEdge(0, 1);
            ptrobj->addEdge(1, 2);
            ptrobj->addEdge(2, 3);
            ptrobj->addEdge(0, 3);

            for (size_t k = 0; k < obj.size(); k++){
               if (ptrobj->needTestWith(*(obj[k]))){
                    if (ptrobj->removeCollisionWith(*(obj[k])).length() > 1e-6){
                        map_vector[i].push_back(1);
                        free = false;  // 1 is blocked
                        break;
                    }
               }
            }
            if (free) {
                map_vector[i].push_back(0);
            }
        } 
    }

    return map_vector;
}
