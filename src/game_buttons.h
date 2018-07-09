#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"
#include "gamelogic/gamelogic.h"
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

    void set_val(int new_exp, int new_hp, int new_mp);

private:
    re::GuiManager& guiManager_;
    GameLogic& game_logic;
    //int mouseX, mouseY;
    int exp = 10, hp = 100, mp = 50;

    Lobby lobby;
};