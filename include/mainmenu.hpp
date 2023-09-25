#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class MainMenu {

private:
    bool show_menu = true;
public:

    Text textMainMenu;
    Text textPlay,textExit;
    RectangleShape playButton, exitButton;
    Font font;

    MainMenu();
    bool isMenuOpen();
    void HideMenu();
    ~MainMenu();
};