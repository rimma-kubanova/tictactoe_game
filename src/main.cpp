#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <mainmenu.hpp>
#include <GameOver.hpp>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(822, 622), "Tic-Tac-Toe", Style::Close | Style::Titlebar);
MainMenu menu;
GameOver gameover;

class Game{
private:
    Texture gridEmptyTexture;
    Texture boardTexture;
    Texture cross;
    Texture circle;
    Font font;
    string msg;
    const char human = 'O';
    const char ai = 'X';

    struct Move {
	    int x;
	    int y;
    };
public:
    int turn;
    Text win;
    Text scoreText;
    Text AIscore;
    Text Humanscore;
    Text resetText;
    enum Player { HUMAN, AI };
    char board[3][3];
    Sprite grid[3][3];
    Sprite boardGrid;
    RectangleShape resetButton;
    void playBoard(Vector2f pos);
    void initializeBoard();
    bool checkWinner(char board[3][3],Player player);
    int score(char board[3][3]);
    bool gameOver(char board[3][3]);
    void playerMove(Sprite grid[3][3]);
    int minimax(char board[3][3], int depth,int alpha, int beta, bool isAI);
    Move AIMove(char board[3][3]);
    void run();
    void reset();
    void AIMove();
};

    void Game::initializeBoard(){
        //board
        boardTexture.loadFromFile("assets/Grid.png");
        boardGrid.setTexture(boardTexture);
        //grid
        gridEmptyTexture.loadFromFile("assets/Nothing.png");
        //cross/circle
        cross.loadFromFile("assets/cross.png");
        circle.loadFromFile("assets/circle.png");
        //text
        font.loadFromFile("assets/font.ttf");

        scoreText.setFont(font);
        scoreText.setString("Score:");
        scoreText.setFillColor(Color::Black);
        scoreText.setPosition(Vector2f(681.0f,30.0f));

        AIscore.setFont(font);
        AIscore.setString("3");
        AIscore.setFillColor(Color::Black);
        AIscore.setPosition(Vector2f(681.0f,100.0f));

        Humanscore.setFont(font);
        Humanscore.setString("0");
        Humanscore.setFillColor(Color::Black);
        Humanscore.setPosition(Vector2f(681.0f,200.0f));

        resetText.setFont(font);
        resetText.setString("Reset!");
        resetText.setFillColor(Color::Black);
        resetText.setOrigin(resetText.getLocalBounds().width/2, resetText.getLocalBounds().height/2);
        resetText.setPosition(Vector2f(411.0f,400.0f));

        win.setFont(font);
        win.setCharacterSize(55);
        win.setFillColor(Color::Black);
        win.setOrigin(win.getLocalBounds().width/2, win.getLocalBounds().height/2);
        win.setPosition(Vector2f(321.0f,250.0f));

        //gameover
        resetButton.setFillColor(Color::Red);
        resetButton.setSize(Vector2f(200.0f,100.0f));
        resetButton.setOrigin(resetButton.getLocalBounds().width/2, resetButton.getLocalBounds().height/2);
        resetButton.setPosition(Vector2f(411.0f,400.0f));

        for(int i = 0; i <3; i++){
            for(int j= 0; j <3 ;j++){
                board[i][j]='-';
                grid[i][j].setTexture(gridEmptyTexture);
                grid[i][j].setScale(1,1);
                grid[i][j].setPosition(Vector2f(200.0f*i+10.0f*i,200.0f*j+10.0f*j));
            }
        }
        turn=0;
    }

    bool Game::checkWinner(char board[3][3],Player player){
        char currentPlayer;
        if(player==HUMAN) currentPlayer = this->human;
        else currentPlayer = this->ai;

        for(int i=0; i<3; i++) {
            // horizontal
            if(board[i][0]==currentPlayer && board[i][1]==currentPlayer && board[i][2]==currentPlayer) return true;
            // vertical
            if(board[0][i]==currentPlayer && board[1][i]==currentPlayer && board[2][i]==currentPlayer) return true;
        }

        //diagonal
        if(board[0][0]==currentPlayer && board[1][1]==currentPlayer && board[2][2]==currentPlayer) return true;
        else if (board[0][2]==currentPlayer && board[1][1]==currentPlayer && board[2][0]==currentPlayer) return true;

        return false;
    }

    int Game::score(char board[3][3]) {
        if(checkWinner(board, HUMAN)) return -10;
        else if(checkWinner(board, AI)) return 10;
        return 0; 
    }

    bool Game::gameOver(char board[3][3]) {
        if(checkWinner(board, HUMAN)) return true;
        else if(checkWinner(board, AI)) return true;

        bool emptySpace = false;
        for(int i = 0; i < 3; i++) {
            if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
                emptySpace = true;
        }
        return !emptySpace;
    }

    int Game::minimax(char board[3][3], int depth,int alpha, int beta, bool isAI){
        int tScore =0, bestScore =0;
        if(gameOver(board)) return score(board);

        if(isAI){
            bestScore = INT_MIN;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    if(this->board[i][j]=='-'){
                        this->board[i][j] = ai;
                        tScore = minimax(board, depth+1, alpha, beta, false);
                        this->board[i][j] = '-';

                        bestScore = max(tScore, bestScore);
                        alpha=max(alpha, bestScore);
                        if(beta<=alpha) break;
                    }
                }
            }
            return bestScore;
        }
        bestScore =INT_MAX;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(this->board[i][j]=='-'){
                    this->board[i][j] = human;
                    tScore = minimax(board, depth+1, alpha, beta, true);
                    this->board[i][j] = '-';

                    bestScore=min(tScore,bestScore);
                    beta=min(beta, bestScore);
                    if(beta<=alpha) break;
                }
            }
        }
        return bestScore;
    }

    Game::Move Game::AIMove(char board[3][3]){
        int tScore =0, bestScore =INT_MIN;
        Move bestMove;

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j]=='-'){
                    board[i][j] = ai;
                    tScore = minimax(board,0,INT_MIN,INT_MAX,false);
                    board[i][j] = '-';
                    if(tScore>bestScore){
                        bestScore = tScore;
                        bestMove.x = i;
                        bestMove.y = j;
                    }
                }
            }
        }
        return bestMove;
    }

    void Game::reset(){
        for(int i=0; i<3;i++){
            for(int j=0; j<3; j++){
                board[i][j] = '-';
                grid[i][j].setTexture(gridEmptyTexture);
            }
        }
        win.setString("");
        turn=0;
        gameover.setGameOver(false);
    }

    void Game::AIMove(){
        Move AImove = AIMove(board);
        this->board[AImove.x][AImove.y] = ai;
        this->grid[AImove.x][AImove.y].setTexture(this->cross);
        if(checkWinner(this->board,AI)){
            this->msg="AI Wins!";
            this->win.setString(this->msg);
            gameover.setGameOver(true);
        }
        turn++;
    }

    void Game::playBoard(Vector2f pos){
        if(this->resetButton.getGlobalBounds().contains(pos)){
            reset();
            return;
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(this->grid[i][j].getGlobalBounds().contains(pos) && this->board[i][j]=='-')
                {
                    this->grid[i][j].setTexture(this->circle);
                    this->board[i][j]=this->human;
                    if(checkWinner(this->board,HUMAN)){
                        this->msg="Human Wins!";
                        this->win.setString(this->msg);
                        gameover.setGameOver(true);
                    };
                    turn++;

                    if(turn==9){
                        this->msg="Draw!";
                        this->win.setString(this->msg);
                        gameover.setGameOver(true);
                    }else
                        AIMove();
                }
            }
        }
}

int main()
{
    Game game;

    game.initializeBoard();

    while (window.isOpen())
        {
            if(menu.isMenuOpen()){
                window.draw(menu.textMainMenu);
                window.draw(menu.playButton);
                window.draw(menu.exitButton);
                window.draw(menu.textPlay);
                window.draw(menu.textExit);
            }else if(gameover.isGameOver())
            {
                window.draw(gameover.screen);
                window.draw(gameover.gameOverText);
                window.draw(game.win);
                window.draw(game.resetButton);
                window.draw(game.resetText);
            }
            else{
                window.clear(Color::White);
                for(int i=0; i<3;i++){
                    for(int j=0; j<3; j++){
                        window.draw(game.grid[i][j]);
                    }
                }
                window.draw(game.boardGrid);
                window.draw(game.scoreText);
                window.draw(game.AIscore);
                window.draw(game.Humanscore);
                // window.draw(game.win);
            }
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
                
                if (event.type == sf::Event::MouseButtonPressed){
				    if(event.mouseButton.button == sf::Mouse::Button::Left){
                        if(menu.isMenuOpen()){
                            if(menu.playButton.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)){
                                menu.HideMenu();
    
                            }else if(menu.exitButton.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)){
                                window.close();
                            }
                        }else
					        game.playBoard(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    }
                }
            }
            window.display();
        }
	return 0;
}
