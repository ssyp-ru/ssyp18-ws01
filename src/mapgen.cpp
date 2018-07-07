#pragma once

#include "map.h"
#include <RealEngine/physic_core.h>
#include <vector>
#include <iostream>
#include "../gamelogic/gamelogic.h"
#include "../events/event_enum.h"
#include <RealEngine/physic_core.h>
#include <fstream>

using namespace std;

int main(){
    vector<vector<int>> obstacles;

    obstacles = generate_obstacles(20, 250, 250, world);


    ofstream fout;
    fout.open("map.txt");
    for (size_t i = 0; i < obstacles.size(); i++){
        for (size_t j = 0; j < obstacles.size(); j++){
            fout << obstacles[i][j];
        }
        fout << std::endl;
    }
    fout.close();

}