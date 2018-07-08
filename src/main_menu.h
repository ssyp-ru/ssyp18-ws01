#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"

#include <iostream>

#include "events/game_event.h"
#include "events/network_event.h"
#include "gamelogic/lobby.h"

enum class MenuState {
    MAIN_MENU,
    IP_INPUT,
    NICK_INPUT
};

class MainMenu {
public:
    MainMenu(re::GuiManager& guiManager);

    void on_key_pressed(re::Key key);
    void setup();
    void display();

    void join_game();
    void create_game();
    void exit_game();
    void set_nick();
    void change_nick();
    void set_ip();
    void connect();
    void go();
    void choose_dark();
    void choose_bright();

private:
    re::GuiManager& guiManager_;
    re::BaseButtonPtr join_game_button_;
    re::BaseButtonPtr create_game_button_;
    re::BaseButtonPtr exit_game_button_;
    re::BaseButtonPtr empty_nick_button_;
    re::BaseButtonPtr change_nick_button_;
    re::BaseButtonPtr connect_button_;
    re::BaseButtonPtr empty_ip_button_;
    re::BaseButtonPtr choose_dark_button_;
    re::BaseButtonPtr choose_bright_button_;
    re::BaseButtonPtr go_button_;
    int mouseX, mouseY;
    re::ImagePtr menuBackground;
    re::ImagePtr players;
    std::string ip;
    std::string nick = "NONAME";
    MenuState menu_state = MenuState::MAIN_MENU;


    Lobby lobby;
};