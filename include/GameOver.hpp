#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GameOver {

private:
    bool is_game_over = false;

public:
    RectangleShape screen;
    Text gameOverText;
    Font font;
    Text winText;
    GameOver();
    void setGameOver(bool value);
    bool isGameOver();

    ~GameOver();
};