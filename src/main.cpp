#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(822, 622), "Tic-Tac-Toe", Style::Close | Style::Titlebar);

class Game{
private:

    Sprite grid[3][3];
    Sprite boardGrid;
    Texture gridTexture;
    const char human = 'O';
    const char ai = 'X';
    char board[3][3];
    enum Player { HUMAN, AI };

    struct Move {
	    int x;
	    int y;
    };
public:
    Game(){
        gridTexture.loadFromFile("assets/Grid.png");
        boardGrid.setTexture(gridTexture);
        // boardGrid.setOrigin(Vector2f(boardGrid.getLocalBounds().width / 2, boardGrid.getLocalBounds().height / 2));
        // boardGrid.setPosition(315, 415);
    }

    void initializeBoard(){
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                board[i][j]= '-';
            }
        }
    }

    bool checkWinner(char board[3][3],Player player){
        char currentPlayer;
        if(player==HUMAN) currentPlayer = human;
        else currentPlayer = ai;

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

    int score(char board[3][3]) {
        if(checkWinner(board, HUMAN)) return -10;
        else if(checkWinner(board, AI)) return 10;
        return 0; 
    }

    bool gameOver(char board[3][3]) {
        if(checkWinner(board, HUMAN)) return true;
        else if(checkWinner(board, AI)) return true;

        bool emptySpace = false;
        for(int i = 0; i < 3; i++) {
            if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
                emptySpace = true;
        }
        return !emptySpace;
    }

    void printBoard(char board[3][3]) {
        cout << "-------------------";
        for(int i=0; i<3; i++) {
            cout<< '\n'<< "|";
            for(int j=0; j<3; j++) {
                cout<< "  "<<board[i][j]<<" "<< " |";
            }
        }
        cout<<'\n'<< "-------------------"<<'\n';
    }

    void playerMove(char board[3][3]){
        int i=0; //from 1 to 9
        while(i<1 || i>9){
            cout<<"Enter your move from 1 to 9:"<<endl;
            cin>>i;
            if(board[(i-1)/3][(i-1)%3]!='-'){
                i=0;
                cout<<"Enter valid move"<<endl;
            }
        }
        int x=(i-1)/3;
        int y=(i-1)%3;

        board[x][y] = human;
    }

    int minimax(char board[3][3], int depth,int alpha, int beta, bool isAI){
        int tScore =0, bestScore =0;
        if(gameOver(board)) return score(board);

        if(isAI){
            bestScore = INT_MIN;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    if(board[i][j]=='-'){
                        board[i][j] = ai;
                        tScore = minimax(board, depth+1, alpha, beta, false);
                        board[i][j] = '-';

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
                if(board[i][j]=='-'){
                    board[i][j] = human;
                    tScore = minimax(board, depth+1, alpha, beta, true);
                    board[i][j] = '-';

                    bestScore=min(tScore,bestScore);
                    beta=min(beta, bestScore);
                    if(beta<=alpha) break;
                }
            }
        }
        return bestScore;
    }

    Move AIMove(char board[3][3]){
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

    void run(){
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(Color(240, 212, 58));
            window.draw(boardGrid);
            window.display();
        }
    }

    void playBoard(){
        initializeBoard();
        int turn = 0;
        printBoard(board);

        while(!checkWinner(board,HUMAN) && !checkWinner(board,AI) && !gameOver(board)){
            if(turn % 2 == 0){
                playerMove(board);
                if(checkWinner(board,HUMAN)) cout<<"Player won";
                turn++;
                printBoard(board);
            }else{
                cout<<"AI move";
                Move AImove = AIMove(board);
                board[AImove.x][AImove.y] = ai;
                if(checkWinner(board,AI)) cout<<"AI won";
                turn++;
                printBoard(board);
            }
        }
    }

};

int main()
{
    Game game;
    game.run();
	// game.playBoard();

	return 0;
}
