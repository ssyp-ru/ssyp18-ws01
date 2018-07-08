#include "main_menu.h"

MainMenu::MainMenu(re::GuiManager& guiManager) 
    : guiManager_(guiManager)
{}

void MainMenu::setup() {
    menuBackground = std::make_shared<re::Image>("menu.png");
    players = std::make_shared<re::Image>("players.png");




    re::ImagePtr skill1_icon = std::make_shared<re::Image>("1.png");
    skill1_button = std::make_shared<re::BaseButton>(700, 20, "skill1", skill1_icon, skill1_icon);
    skill1_button->register_action(std::bind(&MainMenu::skill1, this));
    guiManager_.register_button(skill1_button, "game_menu");

    re::ImagePtr skill2_icon = std::make_shared<re::Image>("2.png");
    skill2_button = std::make_shared<re::BaseButton>(760, 20, "skill2", skill2_icon, skill2_icon);
    skill2_button->register_action(std::bind(&MainMenu::skill2, this));
    guiManager_.register_button(skill2_button, "game_menu");

    re::ImagePtr skill3_icon = std::make_shared<re::Image>("3.png");
    skill3_button = std::make_shared<re::BaseButton>(920, 20, "skill3", skill3_icon, skill3_icon);
    skill3_button->register_action(std::bind(&MainMenu::skill3, this));
    guiManager_.register_button(skill3_button, "game_menu");

    re::ImagePtr skill4_icon = std::make_shared<re::Image>("4.png");
    skill4_button = std::make_shared<re::BaseButton>(970, 20, "skill4", skill4_icon, skill4_icon);
    skill4_button->register_action(std::bind(&MainMenu::skill4, this));
    guiManager_.register_button(skill4_button, "game_menu");

    

}

void MainMenu::display() {
    guiManager_.display(mouseX, mouseY);  
    
}
