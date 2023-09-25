#include "mainmenu.hpp"

MainMenu::MainMenu() {
    font.loadFromFile("assets/font.ttf");

    textMainMenu.setFont(font);
    textMainMenu.setString("Tic-Tac-Toe");
    textMainMenu.setOrigin(textMainMenu.getLocalBounds().width/2, textMainMenu.getLocalBounds().height/2);
    textMainMenu.setPosition(Vector2f(411.0f,100.0f));

    textPlay.setFont(font);
    textPlay.setString("Play");
    textPlay.setOrigin(textPlay.getLocalBounds().width/2, textPlay.getLocalBounds().height/2);
    textPlay.setPosition(Vector2f(411.0f,200.0f));

    textExit.setFont(font);
    textExit.setString("Exit");
    textExit.setOrigin(textExit.getLocalBounds().width/2, textExit.getLocalBounds().height/2);
    textExit.setPosition(Vector2f(411.0f,400.0f));

    playButton.setFillColor(Color::Green);
    playButton.setSize(Vector2f(150.0f,100.0f));
    playButton.setPosition(Vector2f(411.0f,200.0f));
    playButton.setOrigin(playButton.getLocalBounds().width/2, playButton.getLocalBounds().height/2);

    exitButton.setFillColor(Color::Magenta);
    exitButton.setSize(Vector2f(150.0f,100.0f));
    exitButton.setOrigin(exitButton.getLocalBounds().width/2, exitButton.getLocalBounds().height/2);
    exitButton.setPosition(Vector2f(411.0f,400.0f));
}

void MainMenu::HideMenu(){
    show_menu=false;
}

bool MainMenu::isMenuOpen(){
    return show_menu;
}

MainMenu::~MainMenu() {

}
