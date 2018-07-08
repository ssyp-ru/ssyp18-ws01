#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"

#include <iostream>



class MainMenu {
public:
    MainMenu(re::GuiManager& guiManager);

    void setup();
    void display();

    void skill1(){

    }
    void skill2(){

    }
    void skill3(){

    }
    void skill4(){

    }

private:
    re::GuiManager& guiManager_;
    re::BaseButtonPtr skill1_button;
    re::BaseButtonPtr skill2_button;
    re::BaseButtonPtr skill3_button;
    re::BaseButtonPtr skill4_button;
    int mouseX, mouseY;
    re::ImagePtr menuBackground;
    re::ImagePtr players;

    Lobby lobby;
};