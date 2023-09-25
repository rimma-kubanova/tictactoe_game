#include "GameOver.hpp"

GameOver::GameOver() {
    font.loadFromFile("assets/font.ttf");

    screen.setFillColor(Color::Blue);
    screen.setSize(Vector2f(600.0f,400.0f));
    screen.setOrigin(screen.getLocalBounds().width/2, screen.getLocalBounds().height/2);
    screen.setPosition(Vector2f(411.0f,311.0f));
    
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setOrigin(gameOverText.getLocalBounds().width/2, gameOverText.getLocalBounds().height/2);
    gameOverText.setPosition(Vector2f(411.f,200.0f));
    
    winText.setFont(font);
    winText.setPosition(Vector2f(390.f,300.0f));

}

void GameOver::setGameOver(bool value){
    is_game_over = value;
}
bool GameOver::isGameOver(){
    return is_game_over;
}

GameOver::~GameOver() {

}