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

    void Join(){
        std::cout << "Join Game" << std::endl;
        connectButton->set_active(true);
        joinGame->set_active(false);
        ipButton->set_active(true);
    }

    void Create(){
        std::cout << "Create Game" << std::endl;
        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);
    }

    void Exit(){
        std::cout << "Exit Game" << std::endl;
        re::exitApp();
    }

    void Empty(){
        std::cout << "empty button" << std::endl;
        changeNick->set_active(true);
    }
    void Empty2(){
        std::cout << "empty button" << std::endl;
    }

     void Change(){
        std::cout << "change nick" << std::endl;
        changeNick->set_active(false);
    }
     void Connect(){
        std::cout << "connect to server" << std::endl;
        connectButton->set_active(false);
        ipButton->set_active(false);
        joinGame->set_active(true);
        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);
        goButton->set_active(false);
    }

    void Go(){
        std::cout << "GO! GO! GO!" << std::endl;
    }


    void Dark(){
        std::cout << "dark side" << std::endl;
    }

    void Bright(){
        std::cout << "bright side" << std::endl;
    }


private:
    re::GuiManager& guiManager_;
    re::BaseButtonPtr joinGame;
    re::BaseButtonPtr createGame;
    re::BaseButtonPtr exitGame;
    re::BaseButtonPtr emptyGame;
    re::BaseButtonPtr changeNick;
    re::BaseButtonPtr connectButton;
    re::BaseButtonPtr ipButton;
    re::BaseButtonPtr dark;
    re::BaseButtonPtr bright;
    re::BaseButtonPtr goButton;
    int mouseX, mouseY;
    re::ImagePtr menuBackground;
    re::ImagePtr players;
};