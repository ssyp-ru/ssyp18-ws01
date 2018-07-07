#pragma once
#include "RealEngine/baseApp.h"
#include "RealEngine/math.h"
#include "RealEngine/gui/base_button.h"
#include "RealEngine/gui/gui_manager.h"

#include <iostream>

#include "events/network_event.h"
#include "gamelogic/lobby.h"

class MainMenu {
public:
    MainMenu(re::GuiManager& guiManager);

    void setup();
    void display();

    void join_name(){
        std::cout << "Join Game" << std::endl;
        connect_button_->set_active(true);
        join_game_button_->set_active(false);
        empty_ip_button_->set_active(true);
    }

    void create_game(){
        std::cout << "Create Game" << std::endl;

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
        std::cout << "Exit Game" << std::endl;
        re::exitApp();
    }

    void set_nick(){
        std::cout << "empty button" << std::endl;
        change_nick_button_->set_active(true);
    }
    void set_ip(){
        std::cout << "empty button" << std::endl;
    }

     void change_nick(){
        std::cout << "change nick" << std::endl;
        change_nick_button_->set_active(false);
    }
     void connect(){
        std::cout << "connect to server" << std::endl;
        connect_button_->set_active(false);
        empty_ip_button_->set_active(false);
        join_game_button_->set_active(true);
        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);

        auto connect_event = std::make_shared<NetworkConnectEvent>( "127.0.0.1", 11999 );
        re::publish_event( connect_event );
        go_button_->set_active(false);
    }

    void go(){
        std::cout << "GO! GO! GO!" << std::endl;
    }


    void choose_dark(){
        std::cout << "choose_dark_button_ side" << std::endl;

        auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( "Some evil player", 1 , lobby.get_self_id() );
        lobby_switch_event->set_shared(true);
        re::publish_event( lobby_switch_event );
    }

    void choose_bright(){
        std::cout << "choose_bright_button_ side" << std::endl;

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

    Lobby lobby;
};