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

    void Join(){
        std::cout << "Join Game" << std::endl;
        connectButton->set_active(true);
        joinGame->set_active(false);
        ipButton->set_active(true);
    }

    void Create(){
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

        auto connect_event = std::make_shared<NetworkConnectEvent>( "127.0.0.1", 11999 );
        re::publish_event( connect_event );
    }

    void Go(){
        std::cout << "GO! GO! GO!" << std::endl;
    }


    void Dark(){
        auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( "Some evil player", 1 , lobby.get_self_id() );
        lobby_switch_event->set_shared(true);
        re::publish_event( lobby_switch_event );

        std::cout << "dark side" << std::endl;
    }

    void Bright(){
        auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( "Some good player", 0, lobby.get_self_id()  );
        lobby_switch_event->set_shared(true);
        re::publish_event( lobby_switch_event );

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

    Lobby lobby;
};