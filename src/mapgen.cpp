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
    for (int i = 0; i < 250; i++){
        for (int j = 0; j < 250; j++){
            if (obstacles[i][j] == 1){
                fout << obstacles[i][j];
            }
            else{
                fout << obstacles[i][j];
            }
        }
        fout << std::endl;
    }
    fout.close();

}