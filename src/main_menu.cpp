#include "main_menu.h"

MainMenu::MainMenu(re::GuiManager& guiManager) 
    : guiManager_(guiManager)
{}

void MainMenu::setup() {
    menuBackground = std::make_shared<re::Image>("menu.png");
    players = std::make_shared<re::Image>("players.png");




    re::ImagePtr joinIcon = std::make_shared<re::Image>("join.png");
    joinGame = std::make_shared<re::BaseButton>(20, 220, "join", joinIcon, joinIcon);
    joinGame->register_action(std::bind(&MainMenu::Join, this));
    guiManager_.register_button(joinGame, "main_menu");

    re::ImagePtr createIcon = std::make_shared<re::Image>("create.png");
    createGame = std::make_shared<re::BaseButton>(20, 520, "create", createIcon, createIcon);
    createGame->register_action(std::bind(&MainMenu::Create, this));
    guiManager_.register_button(createGame, "main_menu");

    re::ImagePtr exitIcon = std::make_shared<re::Image>("exit.png");
    exitGame = std::make_shared<re::BaseButton>(20, 720, "exit", exitIcon, exitIcon);
    exitGame->register_action(std::bind(&MainMenu::Exit, this));
    guiManager_.register_button(exitGame, "main_menu");

    re::ImagePtr emptyIcon = std::make_shared<re::Image>("empty.png");
    emptyGame = std::make_shared<re::BaseButton>(20, 20, "empty", emptyIcon, emptyIcon);
    emptyGame->register_action(std::bind(&MainMenu::Empty, this));
    guiManager_.register_button(emptyGame, "main_menu");

    re::ImagePtr changeIcon = std::make_shared<re::Image>("change.png");
    changeNick = std::make_shared<re::BaseButton>(20, 120, "change", changeIcon, changeIcon);
    changeNick->register_action(std::bind(&MainMenu::Change, this));
    guiManager_.register_button(changeNick, "main_menu");
    changeNick->set_active(false);
    

    re::ImagePtr connectIcon = std::make_shared<re::Image>("connect.png");
    connectButton = std::make_shared<re::BaseButton>(20, 320, "connect", connectIcon, connectIcon);
    connectButton->register_action(std::bind(&MainMenu::Connect, this));
    guiManager_.register_button(connectButton, "main_menu");
    connectButton->set_active(false);

    re::ImagePtr ipIcon = std::make_shared<re::Image>("empty.png");
    ipButton = std::make_shared<re::BaseButton>(20, 220, "ip", ipIcon, ipIcon);
    ipButton->register_action(std::bind(&MainMenu::Empty2, this));
    guiManager_.register_button(ipButton, "main_menu");
    ipButton->set_active(false);


    re::ImagePtr darkIcon = std::make_shared<re::Image>("dark.png");
    dark = std::make_shared<re::BaseButton>(20, 760, "dark", darkIcon, darkIcon);
    dark->register_action(std::bind(&MainMenu::Dark, this));
    guiManager_.register_button(dark, "select_side");


    re::ImagePtr brightIcon = std::make_shared<re::Image>("bright.png");
    bright = std::make_shared<re::BaseButton>(20, 360, "bright", brightIcon, brightIcon);
    bright->register_action(std::bind(&MainMenu::Bright, this));
    guiManager_.register_button(bright, "select_side");


    re::ImagePtr goIcon = std::make_shared<re::Image>("go.png");
    goButton = std::make_shared<re::BaseButton>(420, 360, "go", goIcon, goIcon);
    goButton->register_action(std::bind(&MainMenu::Go, this));
    guiManager_.register_button(goButton, "select_side");

    guiManager_.layer_set_active("select_side", false);

}

void MainMenu::display() {
    re::draw_image(0, 0, menuBackground);
    guiManager_.display(mouseX, mouseY);  
    if(dark->is_active()){
        re::draw_image(20, 20, players);
        re::draw_image(20, 420, players);
    }
}
