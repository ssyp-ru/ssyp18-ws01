#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"
#include "gamelogic/gamelogic.h"
#include "gamelogic/lobby.h"
#include "unit.h"
#include "gameobject.h"
#include <iostream>



class GameMenu {
public:
    GameMenu(re::GuiManager& guiManager, GameLogic& gameLogic);

    void setup();
    void display(int mouseX, int mouseY);

    void skill1(); 
    void skill2();
    void skill3();
    void skill4();

    void set_hp(int new_hp);

private:
    re::GuiManager& guiManager_;
    GameLogic& game_logic;
    //int mouseX, mouseY;
    int exp = 10, hp = 100, mp = 50;

    Lobby lobby;
};