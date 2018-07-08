#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"

#include <iostream>

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

    void join_game(){
        connect_button_->set_active(true);
        join_game_button_->set_active(false);
        empty_ip_button_->set_active(true);
        menu_state = MenuState::IP_INPUT;
    }

    void create_game(){

        auto server_up_event = std::make_shared<NetworkServerUpEvent>( 11999 );
        re::publish_event( server_up_event );

        LobbyMember owner;
        owner.name = "owner";
        owner.team = 0;
        
        lobby.join( owner );

        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);
    }

    void exit_game(){
        re::exitApp();
    }

    void set_nick(){
        change_nick_button_->set_active(true);
        menu_state = MenuState::NICK_INPUT;
    }
    void set_ip(){
    }

     void change_nick(){
        change_nick_button_->set_active(false);
        menu_state = MenuState::MAIN_MENU;
    }
     void connect(){
        connect_button_->set_active(false);
        empty_ip_button_->set_active(false);
        join_game_button_->set_active(true);
        menu_state = MenuState::MAIN_MENU;
        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);

        auto connect_event = std::make_shared<NetworkConnectEvent>( "127.0.0.1", 11999 );
        re::publish_event( connect_event );
        go_button_->set_active(false);
    }

    void go(){
        
    }


    void choose_dark(){
        auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( "Some evil player", 1 , lobby.get_self_id() );
        lobby_switch_event->set_shared(true);
        re::publish_event( lobby_switch_event );
    }

    void choose_bright(){
        auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( "Some good player", 0, lobby.get_self_id()  );
        lobby_switch_event->set_shared(true);
        re::publish_event( lobby_switch_event );
    }


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
    std::string nick;
    MenuState menu_state = MenuState::MAIN_MENU;


    Lobby lobby;
};